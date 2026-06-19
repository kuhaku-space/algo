#pragma once
#include <array>
#include <cmath>
#include <cstdint>
#include <vector>

/// @brief エラトステネスの篩
///
/// mod30 の wheel とビットマスクで 1 バイトに 8 個の数を詰める。
/// 篩い込みは L1 キャッシュに収まるセグメント単位で行い（segmented sieve）、
/// 内側ループは 8 ステップ（wheel 1 周）を展開する。
/// @see https://qiita.com/peria/items/a4ff4ddb3336f7b81d50
/// @see https://qiita.com/peria/items/e0ab38f95d16a5f7cc58
/// @see https://qiita.com/peria/items/c1d8523342e81bb23375
template <int N = (1 << 22)>
struct eratosthenes {
  private:
    static constexpr int SIZE = N / 30 + (N % 30 != 0);
    // 1 セグメントのバイト数。L1 キャッシュ（32KB 前後）に収まるよう調整する。
    static constexpr int kSegmentSize = 1 << 15;
    static constexpr std::array<int, 8> kMod30 = {1, 7, 11, 13, 17, 19, 23, 29};
    static constexpr std::array<int, 8> C1 = {6, 4, 2, 4, 2, 4, 6, 2};
    static constexpr std::array<std::array<int, 8>, 8> C0 = {
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 2, 2, 0, 2, 0, 2, 2, 1, 3, 1, 1, 2, 1, 1, 3, 1,
        3, 3, 1, 2, 1, 3, 3, 1, 4, 2, 2, 2, 2, 2, 4, 1, 5, 3, 1, 4, 1, 3, 5, 1, 6, 4, 2, 4, 2, 4, 6, 1,
    };
    static constexpr std::array<std::array<std::uint8_t, 8>, 8> kMask = {
        0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f, 0xfd, 0xdf, 0xef, 0xfe, 0x7f, 0xf7, 0xfb, 0xbf,
        0xfb, 0xef, 0xfe, 0xbf, 0xfd, 0x7f, 0xf7, 0xdf, 0xf7, 0xfe, 0xbf, 0xdf, 0xfb, 0xfd, 0x7f, 0xef,
        0xef, 0x7f, 0xfd, 0xfb, 0xdf, 0xbf, 0xfe, 0xf7, 0xdf, 0xf7, 0x7f, 0xfd, 0xbf, 0xfe, 0xef, 0xfb,
        0xbf, 0xfb, 0xf7, 0x7f, 0xfe, 0xef, 0xdf, 0xfd, 0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe,
    };

    // セグメントを跨いで篩い込み位置を持ち越すための小さい素数の情報。
    struct sieve_prime {
        int i;     // 素数 p = 30*i + kMod30[ibit] のバイト位置
        int ibit;  // p の mod30 wheel での位置
        int j;     // 次に篩う合成数のバイト位置
        int k;     // その合成数の wheel 位置
    };

  public:
    eratosthenes() {
        prime_number.fill(0xff);
        prime_number[0] = 0xfe;
        if (int r = N % 30) {
            if (r < 7) prime_number[SIZE - 1] = 0x1;
            else if (r < 11) prime_number[SIZE - 1] = 0x3;
            else if (r < 13) prime_number[SIZE - 1] = 0x7;
            else if (r < 17) prime_number[SIZE - 1] = 0xf;
            else if (r < 19) prime_number[SIZE - 1] = 0x1f;
            else if (r < 23) prime_number[SIZE - 1] = 0x3f;
            else if (r < 29) prime_number[SIZE - 1] = 0x7f;
        }

        const std::uint64_t sqrt_x = std::ceil(std::sqrt(N) + 0.1);
        const std::uint64_t sqrt_xi = sqrt_x / 30 + 1;

        // √N までを通常の篩で確定させ、各素数の初回篩い位置を記録する。
        // この範囲は小さくキャッシュに収まるのでセグメント化しない。
        std::vector<sieve_prime> primes;
        const std::uint64_t head = std::min<std::uint64_t>(sqrt_xi, SIZE);
        for (std::uint64_t i = 0; i < head; ++i) {
            for (std::uint8_t flags = prime_number[i]; flags; flags &= flags - 1) {
                const int ibit = __builtin_ctz(flags);
                const int m = kMod30[ibit];
                const int pm = 30 * static_cast<int>(i) + 2 * m;
                std::uint64_t j = i * pm + (m * m) / 30;
                int k = ibit;
                // √N 以下の範囲（＝記録した素数の倍数が現れうる head 部分）はここで篩う。
                for (; j < head; j += i * C1[k] + C0[ibit][k], k = (k + 1) & 7) { prime_number[j] &= kMask[ibit][k]; }
                if (j < static_cast<std::uint64_t>(SIZE)) {
                    primes.push_back({static_cast<int>(i), ibit, static_cast<int>(j), k});
                }
            }
        }

        // 残りをセグメント単位で篩う。各素数の位置 (j, k) を持ち越すことで、
        // 書き込みが常にキャッシュ常駐の区間に収まりキャッシュミスを抑える。
        for (int seg_lo = static_cast<int>(head); seg_lo < SIZE; seg_lo += kSegmentSize) {
            const int seg_hi = std::min(seg_lo + kSegmentSize, SIZE);
            for (sieve_prime &sp : primes) {
                const int i = sp.i, ibit = sp.ibit;
                const auto &mask = kMask[ibit];
                const auto &c0 = C0[ibit];
                int j = sp.j, k = sp.k;
                // 前処理: メインループの起点を k == 0 に揃える。
                for (; k != 0 && j < seg_hi; j += i * C1[k] + c0[k], k = (k + 1) & 7) { prime_number[j] &= mask[k]; }
                // メインループ: wheel 1 周（8 ステップ）を展開して分岐を削減する。
                // 8 ステップで進むバイト数は i*sum(C1) + sum(C0[ibit]) = 30*i + p。
                // 8 番目の書き込み位置 j + (30*i + p) - C1[7] - c0[7] が seg_hi 未満なら展開可能。
                if (k == 0) {
                    const int last8 = 30 * i + (30 * i + 2 * kMod30[ibit]) - (i * C1[7] + c0[7]);
                    while (j + last8 < seg_hi) {
                        prime_number[j] &= mask[0];
                        j += i * C1[0] + c0[0];
                        prime_number[j] &= mask[1];
                        j += i * C1[1] + c0[1];
                        prime_number[j] &= mask[2];
                        j += i * C1[2] + c0[2];
                        prime_number[j] &= mask[3];
                        j += i * C1[3] + c0[3];
                        prime_number[j] &= mask[4];
                        j += i * C1[4] + c0[4];
                        prime_number[j] &= mask[5];
                        j += i * C1[5] + c0[5];
                        prime_number[j] &= mask[6];
                        j += i * C1[6] + c0[6];
                        prime_number[j] &= mask[7];
                        j += i * C1[7] + c0[7];
                    }
                }
                // 後処理: セグメント末尾までの残りを 1 ステップずつ。
                for (; j < seg_hi; j += i * C1[k] + c0[k], k = (k + 1) & 7) { prime_number[j] &= mask[k]; }
                sp.j = j;
                sp.k = k;
            }
        }
    }

    /// @brief 素数判定
    bool is_prime(int x) const {
        switch (x % 30) {
            case 1: return prime_number[x / 30] >> 0 & 1;
            case 7: return prime_number[x / 30] >> 1 & 1;
            case 11: return prime_number[x / 30] >> 2 & 1;
            case 13: return prime_number[x / 30] >> 3 & 1;
            case 17: return prime_number[x / 30] >> 4 & 1;
            case 19: return prime_number[x / 30] >> 5 & 1;
            case 23: return prime_number[x / 30] >> 6 & 1;
            case 29: return prime_number[x / 30] >> 7 & 1;
        }
        if (x < 6) {
            if (x == 2) return true;
            if (x == 3) return true;
            if (x == 5) return true;
        }
        return false;
    }

    std::vector<int> prime_numbers(int x) const {
        if (x < 2) return std::vector<int>();
        std::vector<int> res = {2};
        for (int i = 3; i <= x; i += 2) {
            if (is_prime(i)) res.emplace_back(i);
        }
        return res;
    }

  private:
    std::array<std::uint8_t, SIZE> prime_number;
};
