#include <cstdint>
#include <utility>
#include "math/pow.hpp"

std::int64_t gcd(std::int64_t a, std::int64_t b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

std::int64_t gcd(const std::vector<std::int64_t> &v) {
    if (v.empty()) return 1;
    std::int64_t res = v[0];
    for (auto i : v) res = gcd(res, i);
    return res;
}

std::int64_t lcm(std::int64_t a, std::int64_t b) { return a / gcd(a, b) * b; }

std::int64_t lcm(const std::vector<std::int64_t> &v) {
    std::int64_t res = 1;
    for (std::int64_t i : v) res = lcm(res, i);
    return res;
}

std::int64_t floor_div(std::int64_t p, std::int64_t q) {
    std::int64_t res = p / q;
    if (q * res > p) --res;
    return res;
}

std::int64_t ceil_div(std::int64_t p, std::int64_t q) {
    std::int64_t res = p / q;
    if (q * res < p) ++res;
    return res;
}

std::int64_t round_ll(double d) {
    if (d < 0) return -round_ll(-d);
    return std::int64_t(d + 0.5);
}

std::int64_t round_ll(long double d) {
    if (d < 0) return -round_ll(-d);
    return std::int64_t(d + 0.5);
}

constexpr bool is_prime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 7 || n == 61) return true;
    if (n % 2 == 0) return false;
    std::int64_t d = n - 1;
    while (d % 2 == 0) d /= 2;
    constexpr std::int64_t bases[3] = {2, 7, 61};
    for (std::int64_t a : bases) {
        std::int64_t t = d;
        std::int64_t y = pow_mod(a, t, n);
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = y * y % n;
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) return false;
    }
    return true;
}
