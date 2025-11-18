#pragma once
#include <algorithm>
#include <bit>
#include <cassert>
#include <cstdint>
#include <vector>
#include "fft/ntt.hpp"

namespace fps {

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> plus(const std::vector<mint> &f, const std::vector<mint> &g) {
    int n = f.size(), m = g.size();
    int s = std::max(n, m);
    std::vector<mint> res = f;
    res.resize(s);
    for (int i = 0; i < m; ++i) res[i] += g[i];
    return res;
}

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> inv(const std::vector<mint> &h, int deg) {
    assert(!h.empty() && h[0] != mint(0));
    std::vector<mint> res(deg);
    res[0] = h[0].inv();
    for (int d = 1; d < deg; d <<= 1) {
        std::vector<mint> f(2 * d), g(2 * d);
        for (int i = 0; i < std::min((int)h.size(), 2 * d); ++i) f[i] = h[i];
        for (int i = 0; i < d; ++i) g[i] = res[i];
        internal::butterfly(f);
        internal::butterfly(g);
        for (int i = 0; i < 2 * d; ++i) f[i] *= g[i];
        internal::butterfly_inv(f);
        mint id = mint(2 * d).inv();
        for (int i = 0; i < 2 * d; ++i) f[i] *= id;
        for (int i = 0; i < d; ++i) f[i] = 0;
        internal::butterfly(f);
        for (int i = 0; i < 2 * d; ++i) f[i] *= g[i];
        internal::butterfly_inv(f);
        for (int i = 0; i < 2 * d; ++i) f[i] *= id;
        for (int i = d; i < std::min(2 * d, deg); ++i) res[i] = -f[i];
    }
    res.resize(deg);
    return res;
}

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> inv(const std::vector<mint> &h) {
    return inv(h, h.size());
}

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> log(const std::vector<mint> &h, int deg) {
    assert(!h.empty() && h[0] == 1);
    std::vector<mint> f(h.size() - 1);
    for (int i = 0; i < (int)f.size(); ++i) f[i] = h[i + 1] * (i + 1);
    f = convolution(f, inv(h));
    f.resize(deg);
    for (int i = deg - 1; i >= 1; --i) f[i] = f[i - 1] / i;
    f[0] = 0;
    return f;
}

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> log(const std::vector<mint> &h) {
    return log(h, h.size());
}

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> exp(const std::vector<mint> &h, int deg) {
    std::vector<mint> f(deg), g(deg);
    f[0] = 1;
    g[0] = 1;
    for (int d = 1; d < deg; d <<= 1) {
        std::vector<mint> dt(d);
        for (int i = 0; i < d; ++i) dt[i] = h[i] * i;
        std::vector<mint> tf(2 * d), tg(2 * d), sf(d);
        for (int i = 0; i < d; ++i) sf[i] = f[i];
        for (int i = 0; i < d; ++i) tf[i] = f[i];
        for (int i = 0; i < d; ++i) tg[i] = g[i];

        tf = convolution(tf, dt);
        tf.resize(2 * d);
        for (int i = 0; i < d; ++i) tf[i] -= f[i] * i;
        tf = convolution(tf, tg);
        tf.resize(2 * d);
        for (int i = 0; i < d; ++i) tf[i] -= dt[i];
        for (int i = 1; i < 2 * d; ++i) tf[i] = tf[i] / i;
        tf[0] = 0;
        for (int i = 0; i < std::min((int)h.size(), 2 * d); ++i) tf[i] += h[i];
        tf = convolution(sf, tf);
        for (int i = d; i < std::min(deg, 2 * d); ++i) f[i] = tf[i];

        std::vector<mint> ft(2 * d), gt(2 * d);
        for (int i = 0; i < 2 * d; ++i) ft[i] = f[i];
        for (int i = 0; i < d; ++i) gt[i] = g[i];
        internal::butterfly(ft);
        internal::butterfly(gt);
        for (int i = 0; i < 2 * d; ++i) ft[i] *= gt[i];
        internal::butterfly_inv(ft);
        mint id = mint(2 * d).inv();
        for (int i = 0; i < 2 * d; ++i) ft[i] *= id;
        for (int i = 0; i < d; ++i) ft[i] = 0;
        internal::butterfly(ft);
        for (int i = 0; i < 2 * d; ++i) ft[i] *= gt[i];
        internal::butterfly_inv(ft);
        for (int i = 0; i < 2 * d; ++i) ft[i] *= id;
        for (int i = d; i < std::min(deg, 2 * d); ++i) g[i] = -ft[i];
    }
    return f;
}

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> exp(const std::vector<mint> &h) {
    return exp(h, h.size());
}

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> pow(const std::vector<mint> &h, std::int64_t m, int deg) {
    if (m == 0) {
        std::vector<mint> res(deg, 0);
        res[0] = 1;
        return res;
    }
    if (m == 1) return h;
    if (m < 0) return inv(pow(h, -m, deg));

    int n = h.size();
    int k = 0;
    while (k < n && h[k] == 0) ++k;
    if (k >= (deg + m - 1) / m) return std::vector<mint>(deg);
    mint c = h[k];
    mint ic = c.inv();
    mint pc = c.pow(m);
    std::vector<mint> res = h;
    res.erase(res.begin(), res.begin() + k);
    for (int i = 0; i < n - k; ++i) res[i] *= ic;
    res = log(res, deg - k * m);
    for (int i = 0; i < deg; ++i) res[i] *= m;
    res = exp(res, deg - k * m);
    for (int i = 0; i < deg - k * m; ++i) res[i] *= pc;
    res.insert(res.begin(), k * m, mint());
    return res;
}

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> pow(const std::vector<mint> &h, std::int64_t m) {
    return pow(h, m, h.size());
}

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::pair<std::vector<mint>, std::vector<mint>> div_mod(std::vector<mint> f, std::vector<mint> g) {
    while (!f.empty() && f.back() == mint()) f.pop_back();
    while (!g.empty() && g.back() == mint()) g.pop_back();
    assert(!g.empty());
    int n = f.size(), m = g.size();
    if (n < m) return {std::vector<mint>(), f};
    std::reverse(f.begin(), f.end());
    std::reverse(g.begin(), g.end());
    std::vector<mint> q = convolution(f, inv(g, n - m + 1));
    q.resize(n - m + 1);
    std::reverse(f.begin(), f.end());
    std::reverse(g.begin(), g.end());
    std::reverse(q.begin(), q.end());
    std::vector<mint> p = convolution(g, q);
    std::vector<mint> r = f;
    r.resize(std::min(n, m - 1));
    for (int i = 0; i < std::min(n, m - 1); ++i) r[i] -= p[i];
    while (!q.empty() && q.back() == mint()) q.pop_back();
    while (!r.empty() && r.back() == mint()) r.pop_back();
    return {q, r};
}

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> div(const std::vector<mint> &f, const std::vector<mint> &g) {
    return div_mod(f, g).first;
}

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> mod(const std::vector<mint> &f, const std::vector<mint> &g) {
    return div_mod(f, g).second;
}

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> multipoint_evaluation(const std::vector<mint> &f, const std::vector<mint> &x) {
    int n = x.size();
    int m = std::bit_ceil<unsigned>(n);
    std::vector<std::vector<mint>> mul(m << 1, {1}), g(m << 1);
    for (int i = 0; i < n; ++i) mul[m + i] = {-x[i], 1};
    for (int i = m - 1; i >= 1; --i) mul[i] = convolution(mul[i << 1 | 0], mul[i << 1 | 1]);

    g[1] = mod(f, mul[1]);
    for (int i = 2; i < m + n; ++i) g[i] = mod(g[i >> 1], mul[i]);
    std::vector<mint> res(n);
    for (int i = 0; i < n; ++i) {
        if (!g[m + i].empty()) res[i] = g[m + i].front();
    }
    return res;
}

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> polynomial_interpolation(const std::vector<mint> &x, const std::vector<mint> &y) {
    int n = x.size();
    int m = std::bit_ceil<unsigned>(n);
    std::vector<std::vector<mint>> mul(m << 1, {1}), g(m << 1);
    for (int i = 0; i < n; ++i) mul[m + i] = {-x[i], 1};
    for (int i = m; i-- > 1;) mul[i] = convolution(mul[i << 1 | 0], mul[i << 1 | 1]);

    std::vector<mint> f = mul[1];
    f.erase(f.begin());
    for (int i = 0; i < n; ++i) f[i] *= i + 1;

    g[1] = mod(f, mul[1]);
    for (int i = 2; i < m + n; ++i) g[i] = mod(g[i >> 1], mul[i]);
    for (int i = 0; i < n; ++i) g[m + i] = {y[i] / g[m + i][0]};
    for (int i = m; i--;)
        g[i] = plus(convolution(g[i << 1 | 0], mul[i << 1 | 1]), convolution(g[i << 1 | 1], mul[i << 1 | 0]));
    return g[1];
}

}  // namespace fps
