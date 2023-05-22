#include "template/template.hpp"

/**
 * @brief エラトステネスの篩
 *
 * @see https://qiita.com/peria/items/a4ff4ddb3336f7b81d50
 */
template <int N = (1 << 22)>
struct eratosthenes {
  private:
    static constexpr int SIZE = N / 30 + (N % 30 != 0);
    static constexpr std::array<int, 8> kMod30 = {1, 7, 11, 13, 17, 19, 23, 29};
    static constexpr std::array<int, 8> C1 = {6, 4, 2, 4, 2, 4, 6, 2};
    static constexpr std::array<std::array<int, 8>, 8> C0 = {
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 2, 2, 0, 2, 0, 2,
        2, 1, 3, 1, 1, 2, 1, 1, 3, 1, 3, 3, 1, 2, 1, 3, 3, 1, 4, 2, 2, 2,
        2, 2, 4, 1, 5, 3, 1, 4, 1, 3, 5, 1, 6, 4, 2, 4, 2, 4, 6, 1,
    };
    static constexpr std::array<std::array<std::uint8_t, 8>, 8> kMask = {
        0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f, 0xfd, 0xdf, 0xef, 0xfe, 0x7f,
        0xf7, 0xfb, 0xbf, 0xfb, 0xef, 0xfe, 0xbf, 0xfd, 0x7f, 0xf7, 0xdf, 0xf7, 0xfe,
        0xbf, 0xdf, 0xfb, 0xfd, 0x7f, 0xef, 0xef, 0x7f, 0xfd, 0xfb, 0xdf, 0xbf, 0xfe,
        0xf7, 0xdf, 0xf7, 0x7f, 0xfd, 0xbf, 0xfe, 0xef, 0xfb, 0xbf, 0xfb, 0xf7, 0x7f,
        0xfe, 0xef, 0xdf, 0xfd, 0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe,
    };

  public:
    constexpr eratosthenes() {
        this->prime_number.fill(0xff);
        this->prime_number[0] = 0xfe;
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
        for (std::uint64_t i = 0; i < sqrt_xi; ++i) {
            for (std::uint8_t flags = prime_number[i]; flags; flags &= flags - 1) {
                std::uint8_t lsb = flags & (-flags);
                const int ibit = __builtin_ctz(lsb);
                const int m = kMod30[ibit];
                const int pm = 30 * i + 2 * m;
                for (std::uint64_t j = i * pm + (m * m) / 30, k = ibit; j < SIZE;
                     j += i * C1[k] + C0[ibit][k], k = (k + 1) & 7) {
                    prime_number[j] &= kMask[ibit][k];
                }
            }
        }
    }

    /**
     * @brief 素数判定
     *
     * @param x
     * @return bool
     */
    bool is_prime(int x) const {
        switch (x % 30) {
            case 1:
                return prime_number[x / 30] >> 0 & 1;
            case 7:
                return prime_number[x / 30] >> 1 & 1;
            case 11:
                return prime_number[x / 30] >> 2 & 1;
            case 13:
                return prime_number[x / 30] >> 3 & 1;
            case 17:
                return prime_number[x / 30] >> 4 & 1;
            case 19:
                return prime_number[x / 30] >> 5 & 1;
            case 23:
                return prime_number[x / 30] >> 6 & 1;
            case 29:
                return prime_number[x / 30] >> 7 & 1;
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
            if (this->is_prime(i)) res.emplace_back(i);
        }
        return res;
    }

  private:
    std::array<std::uint8_t, SIZE> prime_number;
};
