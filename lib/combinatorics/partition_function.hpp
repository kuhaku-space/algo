#pragma once
#include <vector>
#include "convolution/formal_power_series.hpp"
#include "math/modint.hpp"

/// @brief 分割数を $p(0)$ から $p(n)$ まで列挙する
/// @details 生成関数 $\prod_{k\ge1}(1-x^k)^{-1}$ の分母を五角数定理で構築し、
/// 形式的冪級数の逆元を求める。
/// @tparam mint NTTを利用できる static modint 型
/// @param n 求める最大の添字。0以上であること
/// @return 長さ $n+1$ の列。i番目の要素は分割数 $p(i)$
/// @complexity $O(n\log n)$
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
