#pragma once
#include <cstdint>

namespace internal {

namespace min_linear {

std::int64_t min_linear(std::int64_t n, std::int64_t m, std::int64_t a, std::int64_t b, bool is_min, std::int64_t p,
                        std::int64_t q) {
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

/// @brief $0\le x<n$ における $(ax+b)\bmod m$ の最小値を返す
/// @param n 探索する項数。1以上
/// @param m 法。1以上
/// @param a 法で正規化された一次係数
/// @param b 法で正規化された定数項
/// @return 一次式の剰余の最小値
/// @complexity $O(\log m)$
/// @see https://judge.yosupo.jp/submission/102303
std::int64_t min_linear(std::int64_t n, std::int64_t m, std::int64_t a, std::int64_t b) {
    return internal::min_linear::min_linear(n, m, a, b, true, 1, 1);
}
