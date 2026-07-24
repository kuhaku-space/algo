#pragma once
#include <vector>
#include "combinatorics/combination.hpp"
#include "convolution/formal_power_series.hpp"
#include "convolution/ntt.hpp"

/// @brief 第1種スターリング数（符号付き）s(n, 0), s(n, 1), ..., s(n, n) を求める（行）
/// @details 下降階乗 $x(x-1)\cdots(x-n+1)=\sum_k s(n,k)x^k$ を
/// 分割統治とNTTによる多項式積で構築する。
/// @tparam mint NTTを利用できる static modint 型
/// @param n 行番号。0以上であること
/// @return 長さ $n+1$ の列。k番目の要素は符号付き第1種スターリング数 $s(n,k)$
/// @complexity $O(n\log^2 n)$
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

/// @brief 第1種スターリング数（符号付き）s(0,k), s(1,k), ..., s(n,k) を求める（列固定）
/// @details 指数型生成関数
/// $\sum_m s(m,k)x^m/m!=\log(1+x)^k/k!$ を利用する。
/// @tparam mint NTTを利用できる static modint 型
/// @param n 求める最大の行番号。0以上であること
/// @param k 固定する列番号。0以上であること
/// @return 長さ $n+1$ の列。m番目の要素は符号付き第1種スターリング数 $s(m,k)$
/// @complexity $O(n\log n)$
template <internal::static_modint_c mint>
std::vector<mint> stirling1_fixed_k(int n, int k) {
    Combinatorics<mint> comb;
    std::vector<mint> v(n + 1, mint(0));
    v[0] = 1;
    if (n >= 1) v[1] = 1;
    auto l = fps::log(v, n + 1);
    auto g = fps::pow(l, k, n + 1);
    std::vector<mint> res(n + 1);
    for (int i = 0; i <= n; ++i) res[i] = g[i] * comb.fact(i) * comb.finv(k);
    return res;
}

/// @brief 第2種スターリング数 S(n, 0), S(n, 1), ..., S(n, n) を求める（行）
/// @details $S(n,k)=\frac{1}{k!}\sum_{i=0}^{k}(-1)^{k-i}\binom{k}{i}i^n$
/// を2列の畳み込みとして計算する。
/// @tparam mint NTTを利用できる static modint 型
/// @param n 行番号。0以上であること
/// @return 長さ $n+1$ の列。k番目の要素は第2種スターリング数 $S(n,k)$
/// @complexity $O(n\log n)$
template <internal::static_modint_c mint>
std::vector<mint> stirling2(int n) {
    Combinatorics<mint> comb;
    std::vector<mint> a(n + 1), b(n + 1);
    for (int i = 0; i <= n; ++i) {
        a[i] = mint(i).pow(n) * comb.finv(i);
        b[i] = (i & 1) ? -comb.finv(i) : comb.finv(i);
    }
    auto c = convolution(a, b);
    c.resize(n + 1);
    return c;
}

/// @brief 第2種スターリング数 S(0,k), S(1,k), ..., S(n,k) を求める（列固定）
/// @details 指数型生成関数
/// $\sum_m S(m,k)x^m/m!=(e^x-1)^k/k!$ を利用する。
/// @tparam mint NTTを利用できる static modint 型
/// @param n 求める最大の行番号。0以上であること
/// @param k 固定する列番号。0以上であること
/// @return 長さ $n+1$ の列。m番目の要素は第2種スターリング数 $S(m,k)$
/// @complexity $O(n\log n)$
template <internal::static_modint_c mint>
std::vector<mint> stirling2_fixed_k(int n, int k) {
    Combinatorics<mint> comb;
    std::vector<mint> f(n + 1, mint(0));
    for (int i = 1; i <= n; ++i) f[i] = comb.finv(i);
    auto h = fps::pow(f, k, n + 1);
    std::vector<mint> res(n + 1);
    for (int i = 0; i <= n; ++i) res[i] = h[i] * comb.fact(i) * comb.finv(k);
    return res;
}
