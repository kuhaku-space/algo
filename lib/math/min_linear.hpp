#pragma once
#include <cstdint>

namespace internal {

namespace min_linear {

std::int64_t min_linear(std::int64_t n, std::int64_t m, std::int64_t a, std::int64_t b, bool is_min,
                        std::int64_t p, std::int64_t q) {
    if (a == 0) return b;
    if (is_min) {
        if (b >= a) {
            std::int64_t t = (m - b + a - 1) / a;
            std::int64_t c = (t - 1) * p + q;
            if (n <= c) return b;
            n -= c;
            b += a * t - m;
        }
        b = a - 1 - b;
    } else {
        if (b < m - a) {
            std::int64_t t = (m - b - 1) / a;
            std::int64_t c = t * p;
            if (n <= c) return a * ((n - 1) / p) + b;
            n -= c;
            b += a * t;
        }
        b = m - 1 - b;
    }
    std::int64_t d = m / a;
    std::int64_t c = min_linear(n, a, m % a, b, !is_min, (d - 1) * p + q, d * p + q);
    return is_min ? a - 1 - c : m - 1 - c;
}

}  // namespace min_linear

}  // namespace internal

/**
 * @brief min of mod of linear
 * @details min (ax + b) mod m | 0 <= x < n
 * @see https://judge.yosupo.jp/submission/102303
 *
 * @param n
 * @param m
 * @param a
 * @param b
 * @return std::int64_t
 */
std::int64_t min_linear(std::int64_t n, std::int64_t m, std::int64_t a, std::int64_t b) {
    return internal::min_linear::min_linear(n, m, a, b, true, 1, 1);
}
