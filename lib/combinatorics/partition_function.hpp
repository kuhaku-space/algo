#pragma once
#include <vector>
#include "convolution/formal_power_series.hpp"
#include "math/modint.hpp"

/// @brief 分割数 p(0), p(1), ..., p(n) を求める
// 生成関数 prod_{k>=1} 1/(1 - x^k) = sum p(n) x^n。
// 分母 prod (1 - x^k) は五角数定理より非ゼロ項が O(sqrt n) 個なので
// O(n) で構築でき、その逆元を FPS inv で取って O(n log n)。
template <internal::static_modint_c mint>
std::vector<mint> partition_function(int n) {
    std::vector<mint> den(n + 1);
    den[0] = 1;
    // 一般五角数 g = k(3k-1)/2 (k = 1, -1, 2, -2, ...) について
    // 係数 (-1)^k を立てる。符号は 2 個ごとに反転する。
    for (int k = 1;; ++k) {
        long long g1 = (long long)k * (3 * k - 1) / 2;
        long long g2 = (long long)k * (3 * k + 1) / 2;
        if (g1 > n) break;
        mint sign = (k & 1) ? mint(-1) : mint(1);
        den[g1] += sign;
        if (g2 <= n) den[g2] += sign;
    }
    return fps::inv(den, n + 1);
}
