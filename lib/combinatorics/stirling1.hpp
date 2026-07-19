#pragma once
#include <vector>
#include "convolution/ntt.hpp"

/// @brief 第1種スターリング数（符号付き）s(n, 0), s(n, 1), ..., s(n, n) を求める
// 下降階乗 x(x-1)(x-2)...(x-n+1) = sum s(n,k) x^k を分割統治 + NTT 乗算で構築する。
// O(n log^2 n)。
template <internal::static_modint_c mint>
std::vector<mint> stirling1(int n) {
    if (n == 0) return std::vector<mint>(1, mint(1));

    auto solve = [](auto &&self, int l, int r) -> std::vector<mint> {
        if (r - l == 1) return {mint(-l), mint(1)};
        int m = l + (r - l) / 2;
        return convolution(self(self, l, m), self(self, m, r));
    };
    return solve(solve, 0, n);
}
