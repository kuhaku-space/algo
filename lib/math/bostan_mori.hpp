#pragma once
#include <vector>
#include "fft/ntt.hpp"

/**
 * @brief Bostan-Mori法
 *
 * @tparam mint
 * @param p
 * @param q
 * @param n
 * @return mint
 */
template <class mint>
mint bostan_mori(std::vector<mint> p, std::vector<mint> q, std::int64_t n) {
    if (n < 0) return 0;
    while (n > 0) {
        if (p.size() >= q.size()) p.resize(q.size() - 1);
        std::vector<mint> q_minus = q;
        for (int i = 1; i < (int)q_minus.size(); i += 2) q_minus[i] = -q_minus[i];
        p = convolution(p, q_minus);
        q = convolution(q, q_minus);
        for (int i = (n & 1); i < (int)p.size(); i += 2) p[i >> 1] = p[i];
        for (int i = 0; i < (int)q.size(); i += 2) q[i >> 1] = q[i];
        p.resize((p.size() + !(n & 1)) / 2);
        q.resize((q.size() + 1) / 2);
        n >>= 1;
    }
    return p[0] / q[0];
}

/**
 * @brief 線形漸化式のN項目
 * a_i = \sum_{j=1}^d c_j a_{i-j} (i >= d)
 *
 * @tparam mint
 * @param a initial terms a_0, ..., a_{d-1}
 * @param c recurrence coefficients c_1, ..., c_d
 * @param n
 * @return mint
 */
template <class mint>
mint kth_term(std::vector<mint> a, std::vector<mint> c, std::int64_t n) {
    assert(a.size() == c.size());
    int d = a.size();
    if (n < d) return a[n];
    std::vector<mint> q(d + 1);
    q[0] = 1;
    for (int i = 0; i < d; ++i) q[i + 1] = -c[i];
    std::vector<mint> p = convolution(a, q);
    p.resize(d);
    return bostan_mori(p, q, n);
}
