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
        std::uint64_t x, y, z, ys, q = 1;
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
                z = x + n - (ys = f(ys));
                if (z >= n) z -= n;
                g = std::gcd(z, n);
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

/// @brief 素因数分解
std::vector<std::uint64_t> factorize(std::uint64_t n) {
    auto res = internal::inner_factorize(n);
    std::sort(res.begin(), res.end());
    return res;
}

std::uint64_t number_of_divisors(std::vector<std::uint64_t> v) {
    std::sort(v.begin(), v.end());
    int c = 0;
    std::uint64_t res = 1;
    for (int i = 0; i < (int)v.size(); ++i) {
        if (i == 0 || v[i] == v[i - 1]) {
            ++c;
        } else {
            res *= c + 1;
            c = 1;
        }
    }
    return res * (c + 1);
}

std::uint64_t number_of_divisors(std::uint64_t n) { return number_of_divisors(internal::inner_factorize(n)); }
