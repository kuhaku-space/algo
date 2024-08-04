#pragma once
#include <cassert>
#include <cstdint>
#include <utility>

namespace internal {

namespace floor_sum {

// @param m `1 <= m`
// @return x mod m
constexpr std::int64_t safe_mod(std::int64_t x, std::int64_t m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

// @param n `n < 2^32`
// @param m `1 <= m < 2^32`
// @return sum_{i=0}^{n-1} floor((ai + b) / m) (mod 2^64)
std::uint64_t floor_sum_unsigned(std::uint64_t n, std::uint64_t m, std::uint64_t a,
                                 std::uint64_t b) {
    std::uint64_t ans = 0;
    while (true) {
        if (a >= m) {
            ans += n * (n - 1) / 2 * (a / m);
            a %= m;
        }
        if (b >= m) {
            ans += n * (b / m);
            b %= m;
        }

        std::uint64_t y_max = a * n + b;
        if (y_max < m) break;
        // y_max < m * (n + 1)
        // floor(y_max / m) <= n
        n = (std::uint64_t)(y_max / m);
        b = (std::uint64_t)(y_max % m);
        std::swap(m, a);
    }
    return ans;
}

}  // namespace floor_sum

}  // namespace internal

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
        std::uint64_t a2 = internal::floor_sum::safe_mod(a, m);
        ans -= 1ULL * n * (n - 1) / 2 * ((a2 - a) / m);
        a = a2;
    }
    if (b < 0) {
        std::uint64_t b2 = internal::floor_sum::safe_mod(b, m);
        ans -= 1ULL * n * ((b2 - b) / m);
        b = b2;
    }
    return ans + internal::floor_sum::floor_sum_unsigned(n, m, a, b);
}
