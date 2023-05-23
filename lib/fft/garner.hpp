#pragma once
#include "internal/internal_math.hpp"
#include "template/template.hpp"

template <class T>
int garner(std::vector<T> r, std::vector<int> m, const int mod) {
    int n = r.size();
    r.emplace_back(0);
    m.emplace_back(mod);

    std::vector<std::int64_t> coffs(n + 1, 1);
    std::vector<std::int64_t> constants(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        int v = (r[i] - constants[i]) * inv_mod(coffs[i], m[i]) % m[i];
        if (v < 0) v += m[i];

        for (int j = i + 1; j < n + 1; ++j) {
            (constants[j] += coffs[j] * v) %= m[j];
            (coffs[j] *= m[i]) %= m[j];
        }
    }

    return constants[n];
}

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
