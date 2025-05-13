#pragma once
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include "internal/internal_math.hpp"
#include "random/xoroshiro128.hpp"

namespace internal {

std::uint64_t pollard_rho(std::uint64_t n) {
    static xoroshiro128 rnd;
    if (~n & 1) return 2;
    if (internal::is_prime_constexpr(n)) return n;
    std::uint64_t r = 0, g = 1;
    auto f = [&](std::uint64_t x) -> std::uint64_t { return ((__uint128_t)x * x + r) % n; };
    std::uniform_int_distribution<std::uint64_t> gen(2, n - 1);
    while (true) {
        std::uint64_t x, y, ys, q = 1;
        r = gen(rnd), y = gen(rnd);
        g = 1;
        constexpr int m = 128;
        for (int r = 1; g == 1; r <<= 1) {
            x = y;
            for (int i = 0; i < r; ++i) y = f(y);
            for (int k = 0; g == 1 && k < r; k += m) {
                ys = y;
                for (int i = 0; i < m && i < r - k; ++i) q = (__uint128_t)q * (x + n - (y = f(y))) % n;
                g = std::gcd(q, n);
            }
        }
        if (g == n) {
            do {
                x += n - (ys = f(ys));
                if (x >= n) x -= n;
                g = std::gcd(x, n);
            } while (g == 1);
        }
        if (g != n) break;
    }
    return g;
}

std::vector<std::uint64_t> inner_factorize(std::uint64_t n) {
    if (n <= 1) return {};
    std::uint64_t p = pollard_rho(n);
    if (p == n) return {p};
    auto l = inner_factorize(p);
    auto r = inner_factorize(n / p);
    std::copy(r.begin(), r.end(), std::back_inserter(l));
    return l;
}

}  // namespace internal

std::vector<std::uint64_t> factorize(std::uint64_t n) {
    auto res = internal::inner_factorize(n);
    std::sort(res.begin(), res.end());
    return res;
}
