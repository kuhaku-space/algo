#pragma once
#include <concepts>
#include <vector>
#include "algorithm/mo.hpp"
#include "math/combination.hpp"
#include "math/modint.hpp"

template <class mint = modint998>
requires(std::derived_from<mint, internal::modint_base>)
std::vector<mint> offline_binomial_sum(const std::vector<std::pair<int, int>> &queries) {
    std::vector<mint> res(queries.size());
    if (queries.empty()) return res;
    int max_n = queries[0].first;
    for (int i = 1; i < (int)queries.size(); ++i) max_n = std::max(max_n, queries[i].first);
    Mo mo(max_n + 1);
    for (int i = 0; i < (int)queries.size(); ++i) mo.add(queries[i].second, queries[i].first);
    Combination<mint> binom;
    mint sum = 1;
    mint inv2 = mint(2).inv();
    int n = 0, k = 0;
    auto al = [&binom, &sum, &n, &k](int) { sum -= binom(n, k--); };
    auto dl = [&binom, &sum, &n, &k](int) { sum += binom(n, ++k); };
    auto ar = [&binom, &sum, &n, &k](int) { sum += sum - binom(n++, k); };
    auto dr = [&binom, &sum, &n, &k, &inv2](int) { sum = (sum + binom(--n, k)) * inv2; };
    auto rem = [&res, &sum](int x) { res[x] = sum; };
    mo.solve(al, ar, dl, dr, rem);
    return res;
}
