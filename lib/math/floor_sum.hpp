#include "internal/internal_math.hpp"
#include "template/template.hpp"

/**
 * @brief floor sum
 *
 * @param n
 * @param m
 * @param a
 * @param b
 * @retval std::int64_t sum[0 <= i < n]floor((a * i + b) / m)
 *
 * @see https://atcoder.github.io/ac-library/production/document_ja/math.html
 */
std::int64_t floor_sum(std::int64_t n, std::int64_t m, std::int64_t a, std::int64_t b) {
    assert(0 <= n && n < (1LL << 32));
    assert(1 <= m && m < (1LL << 32));
    std::uint64_t ans = 0;
    if (a < 0) {
        std::uint64_t a2 = internal::safe_mod(a, m);
        ans -= 1ULL * n * (n - 1) / 2 * ((a2 - a) / m);
        a = a2;
    }
    if (b < 0) {
        std::uint64_t b2 = internal::safe_mod(b, m);
        ans -= 1ULL * n * ((b2 - b) / m);
        b = b2;
    }
    return ans + internal::floor_sum_unsigned(n, m, a, b);
}
