#pragma once
#include "template/template.hpp"

std::int64_t safe_mod(std::int64_t a, std::int64_t mod) {
    a %= mod;
    return a >= 0 ? a : a + mod;
}

std::int64_t pow_int(std::int64_t a, std::int64_t n) {
    assert(n >= 0);
    std::int64_t res = 1, mul = a;
    for (; n > 0; n >>= 1) {
        if (n & 1) res *= mul;
        mul *= mul;
    }
    return res;
}

std::int64_t inv_mod(std::int64_t a, std::int64_t mod) {
    std::int64_t b = mod, u = 1, v = 0, t;
    while (b > 0) {
        t = a / b;
        std::swap(a -= t * b, b);
        std::swap(u -= t * v, v);
    }
    return u >= 0 ? u % mod : (mod - (-u) % mod) % mod;
}

std::int64_t pow_mod(std::int64_t a, std::int64_t n, std::int64_t mod) {
    if (n < 0) return inv_mod(pow_mod(a, -n, mod), mod);
    std::int64_t res = 1, mul = safe_mod(a, mod);
    for (; n > 0; n >>= 1) {
        if (n & 1) (res *= mul) %= mod;
        (mul *= mul) %= mod;
    }
    return res;
}

int ceil_pow2(std::int64_t n) {
    int x = 0;
    while ((std::uint64_t(1) << x) < (std::uint64_t)(n)) ++x;
    return x;
}

int floor_pow2(std::int64_t n) {
    int x = 0;
    while ((std::uint64_t(1) << (x + 1)) <= (std::uint64_t)(n)) ++x;
    return x;
}
