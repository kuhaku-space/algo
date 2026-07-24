#pragma once
#include <vector>
#include "convolution/formal_power_series.hpp"

/// @brief ベル数を $B_0$ から $B_n$ まで列挙する
/// @details 形式的冪級数 $\exp(\exp(x)-1)$ からベル数を求める。
/// @tparam mint NTTを利用できる static modint 型
/// @param n 求める最大の添字。0以上であること
/// @return 長さ $n+1$ の列。i番目の要素はベル数 $B_i$
/// @complexity $O(n\log n)$
template <internal::static_modint_c mint>
std::vector<mint> bell(int n) {
    if (n == 0) return std::vector<mint>(1, mint(1));
    std::vector<mint> res(n + 1);
    res[1] = 1;
    res = fps::exp(res);
    res[0] -= 1;
    res = fps::exp(res);
    mint mul = 1;
    for (int i = 0; i <= n; ++i) {
        res[i] *= mul;
        mul *= i + 1;
    }
    return res;
}
