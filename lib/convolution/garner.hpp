#pragma once
#include <cstdint>
#include <vector>
#include "internal/internal_math.hpp"

/// @brief Garner法で連立合同式の解を指定した法で復元する
/// @tparam T 剰余の整数型
/// @param r 各法における剰余
/// @param m 互いに素な法
/// @param mod 出力を取る法
/// @return $x\bmod mod$
/// @complexity 法の個数を $n$ として $O(n^2)$
template <class T>
int garner(std::vector<T> r, std::vector<int> m, const int mod) {
    int n = r.size();
    r.emplace_back(0);
    m.emplace_back(mod);

    std::vector<std::int64_t> coffs(n + 1, 1);
    std::vector<std::int64_t> constants(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        int v = (r[i] - constants[i]) * internal::inv_gcd(coffs[i], m[i]).second % m[i];
        if (v < 0) v += m[i];

        for (int j = i + 1; j < n + 1; ++j) {
            (constants[j] += coffs[j] * v) %= m[j];
            (coffs[j] *= m[i]) %= m[j];
        }
    }

    return constants[n];
}

/// @brief Garner法で連立合同式の解を指定した法で復元する
/// @tparam mod 出力を取る法
/// @param r 各法における剰余
/// @param m 互いに素な法
/// @return $x\bmod mod$
/// @complexity 法の個数を $n$ として $O(n^2)$
template <int mod>
int garner(std::vector<int> r, std::vector<int> m) {
    int n = r.size();
    r.emplace_back(0);
    m.emplace_back(mod);

    std::vector<std::int64_t> coffs(n + 1, 1);
    std::vector<std::int64_t> constants(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        int v = (r[i] - constants[i]) * internal::inv_gcd(coffs[i], m[i]).second % m[i];
        if (v < 0) v += m[i];

        for (int j = i + 1; j < n + 1; ++j) {
            (constants[j] += coffs[j] * v) %= m[j];
            (coffs[j] *= m[i]) %= m[j];
        }
    }

    return constants[n];
}
