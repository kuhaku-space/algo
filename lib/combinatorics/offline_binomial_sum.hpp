#pragma once
#include <vector>
#include "algorithm/mo.hpp"
#include "combinatorics/combination.hpp"
#include "math/modint.hpp"

/// @brief 複数の二項係数部分和 $\sum_{i=0}^{k}\binom{n}{i}$ をまとめて求める
/// @details Mo's algorithmで $(n,k)$ 間を遷移し、各クエリの答えを入力順に返す。
/// @tparam mint 法が奇素数の modint 型
/// @param queries $(n,k)$ の列。各要素は $0\le k\le n$ を満たすこと
/// @return queriesと同じ長さの列。i番目はi番目のクエリの二項係数部分和
/// @complexity クエリ数を $Q$、最大のnを $N$ として
/// $O((N+Q)\sqrt{Q}+Q\log Q)$
template <internal::modint mint = modint998>
std::vector<mint> offline_binomial_sum(const std::vector<std::pair<int, int>> &queries) {
    std::vector<mint> res(queries.size());
    if (queries.empty()) return res;
    int max_n = queries[0].first;
    for (int i = 1; i < (int)queries.size(); ++i) max_n = std::max(max_n, queries[i].first);
    Mo mo(max_n + 1);
    for (int i = 0; i < (int)queries.size(); ++i) mo.add(queries[i].second, queries[i].first);
    Combinatorics<mint> binom;
    mint sum = 1;
    mint inv2 = mint(2).inv();
    int n = 0, k = 0;
    auto al = [&binom, &sum, &n, &k](int) { sum -= binom.binom(n, k--); };
    auto dl = [&binom, &sum, &n, &k](int) { sum += binom.binom(n, ++k); };
    auto ar = [&binom, &sum, &n, &k](int) { sum += sum - binom.binom(n++, k); };
    auto dr = [&binom, &sum, &n, &k, &inv2](int) { sum = (sum + binom.binom(--n, k)) * inv2; };
    auto rem = [&res, &sum](int x) { res[x] = sum; };
    mo.solve(al, ar, dl, dr, rem);
    return res;
}
