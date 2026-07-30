#pragma once
#include <cassert>
#include <cstdint>
#include <numeric>
#include <optional>
#include <vector>

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

/// @brief オーバーフローを検出する累乗
/// @details $n^k$ が `std::int64_t` に収まるならその値を、収まらないなら `std::nullopt` を返す。
/// 底が負でも扱え、$k = 0$ のときは $0^0 = 1$ を含めて $1$ を返す。
/// @param n 底
/// @param k 指数、`0 <= k`
/// @return 収まるなら $n^k$、収まらないなら `std::nullopt`
/// @complexity $O(\log k)$
constexpr std::optional<std::int64_t> checked_pow(std::int64_t n, std::int64_t k) {
    assert(0 <= k);
    std::int64_t res = 1, mul = n;
    while (k > 0) {
        if (k & 1) {
            if (__builtin_mul_overflow(res, mul, &res)) return std::nullopt;
        }
        k >>= 1;
        // 指数が残っている時だけ二乗する。この時 mul の次の値 $|n|^{2^{j+1}}$ は
        // $2^{j+1} \le k$ より $|n^k|$ 以下なので、収まる答えを取りこぼすことはない。
        if (k > 0) {
            if (__builtin_mul_overflow(mul, mul, &mul)) return std::nullopt;
        }
    }
    return res;
}
