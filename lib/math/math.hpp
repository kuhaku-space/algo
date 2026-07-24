#pragma once
#include <cstdint>
#include <numeric>
#include <utility>
#include <vector>

namespace internal {

constexpr std::int64_t safe_mod(std::int64_t a, std::int64_t mod) {
    a %= mod;
    return a >= 0 ? a : a + mod;
}

constexpr std::int64_t inv_mod(std::int64_t a, std::int64_t mod) {
    std::int64_t b = mod, u = 1, v = 0, t;
    while (b > 0) {
        t = a / b;
        std::swap(a -= t * b, b);
        std::swap(u -= t * v, v);
    }
    return u >= 0 ? u % mod : (mod - (-u) % mod) % mod;
}

constexpr std::int64_t pow_mod(std::int64_t a, std::int64_t n, std::int64_t mod) {
    if (n < 0) return inv_mod(pow_mod(a, -n, mod), mod);
    std::int64_t res = 1, mul = safe_mod(a, mod);
    for (; n > 0; n >>= 1) {
        if (n & 1) (res *= mul) %= mod;
        (mul *= mul) %= mod;
    }
    return res;
}

}  // namespace internal

/// @brief 整数列の最大公約数を返す
/// @complexity 要素数を $n$、絶対値の最大を $M$ として $O(n\log M)$
std::int64_t gcd(const std::vector<std::int64_t> &v) {
    if (v.empty()) return -1;
    std::int64_t res = v[0];
    for (auto e : v) res = std::gcd(res, e);
    return res;
}

/// @brief 整数列の最小公倍数を返す
/// @complexity 要素数を $n$、絶対値の最大を $M$ として $O(n\log M)$
std::int64_t lcm(const std::vector<std::int64_t> &v) {
    if (v.empty()) return -1;
    std::int64_t res = 1;
    for (auto e : v) res = std::lcm(res, e);
    return res;
}

/// @brief $\lfloor p/q\rfloor$ を返す
/// @complexity $O(1)$
std::int64_t floor_div(std::int64_t p, std::int64_t q) {
    std::int64_t res = p / q;
    if (q * res > p) --res;
    return res;
}

/// @brief $\lceil p/q\rceil$ を返す
/// @complexity $O(1)$
std::int64_t ceil_div(std::int64_t p, std::int64_t q) {
    std::int64_t res = p / q;
    if (q * res < p) ++res;
    return res;
}

/// @brief 浮動小数点数を最も近い整数へ丸める
/// @complexity $O(1)$
std::int64_t round_ll(double d) {
    if (d < 0) return -round_ll(-d);
    return std::int64_t(d + 0.5);
}

/// @brief 浮動小数点数を最も近い整数へ丸める
/// @complexity $O(1)$
std::int64_t round_ll(long double d) {
    if (d < 0) return -round_ll(-d);
    return std::int64_t(d + 0.5);
}

/// @brief 32bit符号付き整数の素数判定
/// @details 底2、7、61のMiller–Rabin法を使う。
/// @complexity $O(\log n)$ 回の剰余乗算
constexpr bool is_prime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 7 || n == 61) return true;
    if (n % 2 == 0) return false;
    std::int64_t d = n - 1;
    while (d % 2 == 0) d /= 2;
    constexpr std::int64_t bases[3] = {2, 7, 61};
    for (std::int64_t a : bases) {
        std::int64_t t = d;
        std::int64_t y = internal::pow_mod(a, t, n);
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = y * y % n;
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) return false;
    }
    return true;
}
