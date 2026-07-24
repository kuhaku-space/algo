#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <utility>
#include <vector>
#include "internal/internal_math.hpp"
#include "number_theory/factorize.hpp"

/// @brief 素数判定
/// @details Miller-Rabin 法。`std::uint64_t` の全域で正しい
/// @complexity $O(\log x)$ 回のmod乗算
constexpr bool is_prime(std::uint64_t x) { return internal::is_prime_constexpr(x); }

/// @brief 素因数分解
/// @return (素数, 指数) のペアを素数の昇順で列挙したもの
/// @complexity Pollard's rho により期待 $O(x^{1/4}\log x)$
std::vector<std::pair<std::uint64_t, int>> prime_factorization(std::uint64_t x) {
    std::vector<std::pair<std::uint64_t, int>> res;
    for (auto p : factorize(x)) {
        if (!res.empty() && res.back().first == p) ++res.back().second;
        else res.emplace_back(p, 1);
    }
    return res;
}

/// @brief 約数列挙
/// @return x の約数を昇順に並べたもの
/// @complexity 約数個数を $d(x)$ として、素因数分解に加えて $O(d(x)\log d(x))$
std::vector<std::uint64_t> divisors(std::uint64_t x) {
    std::vector<std::uint64_t> res{1};
    for (auto [p, e] : prime_factorization(x)) {
        int n = (int)res.size();
        res.resize(n * (e + 1));
        for (int i = 0; i < n * e; ++i) res[n + i] = res[i] * p;
        for (int i = 1; i <= e; ++i) {
            std::inplace_merge(res.begin(), res.begin() + n * i, res.begin() + n * (i + 1));
        }
    }
    return res;
}

/// @brief 乗法的分割
/// @return x = f_1 * f_2 * ... * f_k (2 <= f_1 <= f_2 <= ... <= f_k) を満たす (f_1, ..., f_k) をすべて列挙したもの
/// @complexity 出力数と再帰中の約数列挙に比例
std::vector<std::vector<std::uint64_t>> multiplicative_partitions(std::uint64_t x) {
    std::vector<std::vector<std::uint64_t>> res;
    std::vector<std::uint64_t> cur;
    auto dfs = [&](auto &&self, std::uint64_t a) -> void {
        if (a == 1) {
            res.emplace_back(cur);
            return;
        }
        for (auto d : divisors(a)) {
            if (d == 1 || (!cur.empty() && cur.back() > d)) continue;
            cur.emplace_back(d);
            self(self, a / d);
            cur.pop_back();
        }
    };
    dfs(dfs, x);
    return res;
}

/// @brief 素数の篩
///
/// `0 <= x < N` の範囲は前計算した篩で高速に答える。範囲外は上記の free function
/// （Miller-Rabin, Pollard's rho）にフォールバックするため、`Sieve` はどんな大きさの
/// 入力に対しても常に正しい答えを返す（範囲外を assert で弾いていた旧実装とは異なる）。
///
/// 素数判定・列挙はエラトステネスの篩（mod30 wheel + セグメント化）で行う。
/// mod30 の wheel とビットマスクで 1 バイトに 8 個の数を詰め、
/// 篩い込みは L1 キャッシュに収まるセグメント単位で行い（segmented sieve）、
/// 内側ループは 8 ステップ（wheel 1 周）を展開する。
/// @see https://qiita.com/peria/items/a4ff4ddb3336f7b81d50
/// @see https://qiita.com/peria/items/e0ab38f95d16a5f7cc58
/// @see https://qiita.com/peria/items/c1d8523342e81bb23375
///
/// 素因数分解は最小素因数（linear sieve）を使う。上記の素数列挙で得た素数列を種に
/// O(N) で構築するため、`is_prime`/`prime_numbers` だけを使う場合はこの分のメモリ・
/// 構築コストはかからない（`prime_factorization` を初めて呼んだ時に遅延構築する）。
/// @complexity 構築は $O(N\log\log N)$、範囲内の素数判定は $O(1)$
template <int N = (1 << 22)>
struct Sieve {
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
    /// @brief N未満の素数判定表を構築する
    /// @complexity $O(N\log\log N)$
    Sieve() {
        flags.fill(0xff);
        flags[0] = 0xfe;
        if (int r = N % 30) {
            if (r < 7) flags[SIZE - 1] = 0x1;
            else if (r < 11) flags[SIZE - 1] = 0x3;
            else if (r < 13) flags[SIZE - 1] = 0x7;
            else if (r < 17) flags[SIZE - 1] = 0xf;
            else if (r < 19) flags[SIZE - 1] = 0x1f;
            else if (r < 23) flags[SIZE - 1] = 0x3f;
            else if (r < 29) flags[SIZE - 1] = 0x7f;
        }

        const std::uint64_t sqrt_x = std::ceil(std::sqrt(N) + 0.1);
        const std::uint64_t sqrt_xi = sqrt_x / 30 + 1;

        // √N までを通常の篩で確定させ、各素数の初回篩い位置を記録する。
        // この範囲は小さくキャッシュに収まるのでセグメント化しない。
        std::vector<sieve_prime> primes;
        const std::uint64_t head = std::min<std::uint64_t>(sqrt_xi, SIZE);
        for (std::uint64_t i = 0; i < head; ++i) {
            for (std::uint8_t f = flags[i]; f; f &= f - 1) {
                const int ibit = __builtin_ctz(f);
                const int m = kMod30[ibit];
                const int pm = 30 * static_cast<int>(i) + 2 * m;
                std::uint64_t j = i * pm + (m * m) / 30;
                int k = ibit;
                // √N 以下の範囲（＝記録した素数の倍数が現れうる head 部分）はここで篩う。
                for (; j < head; j += i * C1[k] + C0[ibit][k], k = (k + 1) & 7) { flags[j] &= kMask[ibit][k]; }
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
                for (; k != 0 && j < seg_hi; j += i * C1[k] + c0[k], k = (k + 1) & 7) { flags[j] &= mask[k]; }
                // メインループ: wheel 1 周（8 ステップ）を展開して分岐を削減する。
                // 8 ステップで進むバイト数は i*sum(C1) + sum(C0[ibit]) = 30*i + p。
                // 8 番目の書き込み位置 j + (30*i + p) - C1[7] - c0[7] が seg_hi 未満なら展開可能。
                if (k == 0) {
                    const int last8 = 30 * i + (30 * i + 2 * kMod30[ibit]) - (i * C1[7] + c0[7]);
                    while (j + last8 < seg_hi) {
                        flags[j] &= mask[0];
                        j += i * C1[0] + c0[0];
                        flags[j] &= mask[1];
                        j += i * C1[1] + c0[1];
                        flags[j] &= mask[2];
                        j += i * C1[2] + c0[2];
                        flags[j] &= mask[3];
                        j += i * C1[3] + c0[3];
                        flags[j] &= mask[4];
                        j += i * C1[4] + c0[4];
                        flags[j] &= mask[5];
                        j += i * C1[5] + c0[5];
                        flags[j] &= mask[6];
                        j += i * C1[6] + c0[6];
                        flags[j] &= mask[7];
                        j += i * C1[7] + c0[7];
                    }
                }
                // 後処理: セグメント末尾までの残りを 1 ステップずつ。
                for (; j < seg_hi; j += i * C1[k] + c0[k], k = (k + 1) & 7) { flags[j] &= mask[k]; }
                sp.j = j;
                sp.k = k;
            }
        }
    }

    /// @brief 素数判定（範囲外は Miller-Rabin にフォールバックするので任意の x で正しい）
    /// @complexity $x<N$ なら $O(1)$、それ以外は $O(\log x)$ 回のmod乗算
    bool is_prime(std::uint64_t x) const {
        if (x >= (std::uint64_t)N) return ::is_prime(x);
        int xi = (int)x;
        switch (xi % 30) {
            case 1: return flags[xi / 30] >> 0 & 1;
            case 7: return flags[xi / 30] >> 1 & 1;
            case 11: return flags[xi / 30] >> 2 & 1;
            case 13: return flags[xi / 30] >> 3 & 1;
            case 17: return flags[xi / 30] >> 4 & 1;
            case 19: return flags[xi / 30] >> 5 & 1;
            case 23: return flags[xi / 30] >> 6 & 1;
            case 29: return flags[xi / 30] >> 7 & 1;
        }
        if (xi < 6) {
            if (xi == 2) return true;
            if (xi == 3) return true;
            if (xi == 5) return true;
        }
        return false;
    }

    /// @brief x 以下の素数を昇順に列挙
    /// @param x `x < N`
    /// @complexity $O(x)$
    std::vector<int> prime_numbers(int x) const {
        assert(x < N);
        if (x < 2) return std::vector<int>();
        std::vector<int> res = {2};
        for (int i = 3; i <= x; i += 2) {
            if (is_prime(i)) res.emplace_back(i);
        }
        return res;
    }

    /// @brief 素因数分解
    /// @details `x < N` なら最小素因数テーブル（初回呼び出し時に O(N) で遅延構築）で
    /// O(log x)、`x >= N` なら Pollard's rho にフォールバックする
    /// @return (素数, 指数) のペアを素数の昇順で列挙したもの
    /// @complexity 初回の範囲内呼出しは $O(N)$、以後は $O(\log x)$。範囲外は期待 $O(x^{1/4}\log x)$
    std::vector<std::pair<std::uint64_t, int>> prime_factorization(std::uint64_t x) {
        if (x >= (std::uint64_t)N) return ::prime_factorization(x);
        if (lpf.empty()) build_lpf();
        std::vector<std::pair<std::uint64_t, int>> res;
        int xi = (int)x;
        while (xi > 1) {
            int p = lpf[xi];
            int cnt = 0;
            for (; xi % p == 0; xi /= p) ++cnt;
            res.emplace_back(p, cnt);
        }
        return res;
    }

  private:
    std::array<std::uint8_t, SIZE> flags;
    std::vector<int> lpf;

    void build_lpf() {
        lpf.assign(N, 0);
        // 篩で求めた素数列を種にする（この時点で is_prime は O(1) で使える）。
        auto pr = prime_numbers(N - 1);
        for (int p : pr) lpf[p] = p;
        for (int i = 2; i < N; ++i) {
            for (int p : pr) {
                if (p > lpf[i] || (std::int64_t)i * p >= N) break;
                lpf[i * p] = p;
                if (p == lpf[i]) break;
            }
        }
    }
};
