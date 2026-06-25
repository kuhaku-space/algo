#pragma once
#include <algorithm>
#include <bit>
#include <cassert>
#include <cstdint>
#include <vector>
#include "combinatorics/combination.hpp"
#include "convolution/ntt.hpp"
#include "convolution/ntt_avx2.hpp"
#include "internal/internal_fps_avx2.hpp"

namespace fps {

namespace internal_fps {

// AVX2 + Montgomery 版 (inv/exp/log) を使える条件: NTT-friendly な素数 mod < 2^30 で、
// かつ実行時に CPU が AVX2 をサポートしていること。
template <internal::static_modint_c mint>
inline bool use_avx2() {
    constexpr unsigned int mod = (unsigned int)mint::mod();
    if constexpr (mod >= (1u << 30)) {
        return false;
    } else {
        return mint::is_prime_mod() && internal::has_avx2();
    }
}

// mint 列 -> Montgomery u32 列。
template <internal::static_modint_c mint>
std::vector<std::uint32_t> to_mont(const std::vector<mint> &a) {
    using s = internal::avx2::mont<(unsigned int)mint::mod()>;
    std::vector<std::uint32_t> r(a.size());
    for (std::size_t i = 0; i < a.size(); ++i) r[i] = s::to((std::uint32_t)a[i].val());
    return r;
}

// Montgomery u32 列 -> mint 列。
template <internal::static_modint_c mint>
std::vector<mint> from_mont(const std::vector<std::uint32_t> &a) {
    using s = internal::avx2::mont<(unsigned int)mint::mod()>;
    std::vector<mint> r(a.size());
    for (std::size_t i = 0; i < a.size(); ++i) r[i] = mint::raw((int)s::from(a[i]));
    return r;
}

// AVX2 が使えるなら AVX2 NTT 畳み込み、そうでなければ通常の convolution に振り分ける。
// mod >= 2^30 では AVX2 NTT が使えないのでコンパイル時に通常版へ固定する。
template <internal::static_modint_c mint>
std::vector<mint> conv_auto(const std::vector<mint> &a, const std::vector<mint> &b) {
    constexpr unsigned int mod = (unsigned int)mint::mod();
    if constexpr (mod < (1u << 30)) {
        if (use_avx2<mint>()) return convolution_avx2(a, b);
    }
    return convolution(a, b);
}

}  // namespace internal_fps

template <internal::static_modint_c mint>
std::vector<mint> plus(const std::vector<mint> &f, const std::vector<mint> &g) {
    int n = f.size(), m = g.size();
    int s = std::max(n, m);
    std::vector<mint> res = f;
    res.resize(s);
    for (int i = 0; i < m; ++i) res[i] += g[i];
    return res;
}

template <internal::static_modint_c mint>
std::vector<mint> inv(const std::vector<mint> &h, int deg) {
    assert(!h.empty() && h[0] != mint(0));
    constexpr unsigned int mod = (unsigned int)mint::mod();
    if constexpr (mod < (1u << 30)) {
        if (internal_fps::use_avx2<mint>())
            return internal_fps::from_mont<mint>(internal::avx2::inv<mod>(internal_fps::to_mont(h), deg));
    }
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

template <internal::static_modint_c mint>
std::vector<mint> inv(const std::vector<mint> &h) {
    return inv(h, h.size());
}

template <internal::static_modint_c mint>
std::vector<mint> log(const std::vector<mint> &h, int deg) {
    assert(!h.empty() && h[0] == 1);
    constexpr unsigned int mod = (unsigned int)mint::mod();
    if constexpr (mod < (1u << 30)) {
        if (internal_fps::use_avx2<mint>())
            return internal_fps::from_mont<mint>(internal::avx2::log<mod>(internal_fps::to_mont(h), deg));
    }
    std::vector<mint> f(h.size() - 1);
    for (int i = 0; i < (int)f.size(); ++i) f[i] = h[i + 1] * (i + 1);
    f = convolution(f, inv(h, deg));
    f.resize(deg);
    for (int i = deg - 1; i >= 1; --i) f[i] = f[i - 1] / i;
    f[0] = 0;
    return f;
}

template <internal::static_modint_c mint>
std::vector<mint> log(const std::vector<mint> &h) {
    return log(h, h.size());
}

template <internal::static_modint_c mint>
std::vector<mint> exp(const std::vector<mint> &h, int deg) {
    constexpr unsigned int mod = (unsigned int)mint::mod();
    if constexpr (mod < (1u << 30)) {
        if (internal_fps::use_avx2<mint>())
            return internal_fps::from_mont<mint>(internal::avx2::exp<mod>(internal_fps::to_mont(h), deg));
    }
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

template <internal::static_modint_c mint>
std::vector<mint> exp(const std::vector<mint> &h) {
    return exp(h, h.size());
}

template <internal::static_modint_c mint>
std::vector<mint> pow(const std::vector<mint> &h, std::int64_t m, int deg) {
    if (m == 0) {
        std::vector<mint> res(deg, 0);
        res[0] = 1;
        return res;
    }
    if (m == 1) {
        std::vector<mint> res = h;
        res.resize(deg);
        return res;
    }
    if (m < 0) return inv(pow(h, -m, deg));

    int n = h.size();
    int k = 0;
    while (k < n && h[k] == 0) ++k;
    // 全係数 0、または最低次 x^k が m 乗で deg 以上に押し出される場合は全 0。
    if (k == n || (std::int64_t)k >= (deg + m - 1) / m) return std::vector<mint>(deg);
    mint c = h[k];
    mint ic = c.inv();
    mint pc = c.pow(m);
    std::vector<mint> res = h;
    res.erase(res.begin(), res.begin() + k);
    for (int i = 0; i < n - k; ++i) res[i] *= ic;
    res = log(res, deg - k * m);
    for (int i = 0; i < deg - k * m; ++i) res[i] *= m;
    res = exp(res, deg - k * m);
    for (int i = 0; i < deg - k * m; ++i) res[i] *= pc;
    res.insert(res.begin(), k * m, mint());
    return res;
}

template <internal::static_modint_c mint>
std::vector<mint> pow(const std::vector<mint> &h, std::int64_t m) {
    return pow(h, m, h.size());
}

template <internal::static_modint_c mint>
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

template <internal::static_modint_c mint>
std::vector<mint> div(const std::vector<mint> &f, const std::vector<mint> &g) {
    return div_mod(f, g).first;
}

template <internal::static_modint_c mint>
std::vector<mint> mod(const std::vector<mint> &f, const std::vector<mint> &g) {
    return div_mod(f, g).second;
}

namespace internal_fps {

// 多点評価のしきい値。残り点数がこれ以下の部分木は、剰余の再帰をやめて
// Horner 法で直接評価した方が速い (NTT の定数倍を避ける)。
static constexpr int MULTIPOINT_NAIVE_THRESHOLD = 64;

// f mod g (g はモニック前提で正規化済み, 末尾 0 を含まない) を AVX2 対応畳み込みで求める。
// 既存の div_mod と同じ手順だが、剰余だけを返し畳み込みを conv_auto に通す。
// g は呼び出し側で末尾 0 を持たないことを保証する (部分積木のモニック多項式)。
template <internal::static_modint_c mint>
std::vector<mint> mod_monic(std::vector<mint> f, const std::vector<mint> &g) {
    while (!f.empty() && f.back() == mint()) f.pop_back();
    int n = f.size(), m = g.size();
    if (n < m) return f;
    std::vector<mint> fr(f.rbegin(), f.rend()), gr(g.rbegin(), g.rend());
    std::vector<mint> q = conv_auto(fr, inv(gr, n - m + 1));
    q.resize(n - m + 1);
    std::reverse(q.begin(), q.end());
    std::vector<mint> p = conv_auto(g, q);
    std::vector<mint> r(std::min(n, m - 1));
    for (int i = 0; i < (int)r.size(); ++i) r[i] = f[i] - p[i];
    while (!r.empty() && r.back() == mint()) r.pop_back();
    return r;
}

// 部分積木: 葉 leaf[m+i] = (x - x_i)、内部節点はその子の積 (いずれもモニック)。
// up[1] は全積 prod_i (x - x_i)。葉数 m = bit_ceil(n)。空葉は定数 1。
template <internal::static_modint_c mint>
std::vector<std::vector<mint>> subproduct_tree(const std::vector<mint> &x, int m) {
    int n = x.size();
    std::vector<std::vector<mint>> up(m << 1, {mint(1)});
    for (int i = 0; i < n; ++i) up[m + i] = {-x[i], mint(1)};
    for (int i = m; i-- > 1;) up[i] = conv_auto(up[i << 1 | 0], up[i << 1 | 1]);
    return up;
}

// Horner 法で f を x[off..off+cnt) の各点で評価して res[off..] に書き込む。
template <internal::static_modint_c mint>
void evaluate_naive(const std::vector<mint> &f, const std::vector<mint> &x, int off, int cnt, std::vector<mint> &res) {
    for (int k = 0; k < cnt; ++k) {
        mint xi = x[off + k], acc = mint();
        for (int j = (int)f.size(); j-- > 0;) acc = acc * xi + f[j];
        res[off + k] = acc;
    }
}

// 剰余木の下降パス: 節点 i で g = f mod up[i] を持ち、子へ g mod up[child] と下ろす。
// 残り点数がしきい値以下の部分木に達したら、剰余の再帰をやめて Horner 法で直接評価する。
// (下位の木では mod 1 回あたりの NTT 定数倍が点数に見合わないため。)
// up を共有することで補間と評価で部分積木を一度しか作らない。
template <internal::static_modint_c mint>
void evaluate_down(const std::vector<std::vector<mint>> &up, const std::vector<mint> &x, int m, int n, int i,
                   std::vector<mint> f, std::vector<mint> &res) {
    int lo = i, hi = i;
    while (lo < m) lo <<= 1, hi = hi << 1 | 1;
    int off = lo - m;
    int cnt = std::min(hi - m, n - 1) - off + 1;  // この部分木が覆う点数
    if (cnt <= 0) return;
    if (cnt <= MULTIPOINT_NAIVE_THRESHOLD) {
        evaluate_naive(f, x, off, cnt, res);
        return;
    }
    evaluate_down(up, x, m, n, i << 1 | 0, mod_monic(f, up[i << 1 | 0]), res);
    evaluate_down(up, x, m, n, i << 1 | 1, mod_monic(std::move(f), up[i << 1 | 1]), res);
}

}  // namespace internal_fps

template <internal::static_modint_c mint>
std::vector<mint> multipoint_evaluation(const std::vector<mint> &f, const std::vector<mint> &x) {
    int n = x.size();
    if (n == 0) return {};
    if (n <= internal_fps::MULTIPOINT_NAIVE_THRESHOLD) {
        std::vector<mint> res(n);
        internal_fps::evaluate_naive(f, x, 0, n, res);
        return res;
    }
    int m = std::bit_ceil<unsigned>(n);
    auto up = internal_fps::subproduct_tree(x, m);
    std::vector<mint> res(n);
    internal_fps::evaluate_down(up, x, m, n, 1, internal_fps::mod_monic(f, up[1]), res);
    return res;
}

template <internal::static_modint_c mint>
std::vector<mint> polynomial_interpolation(const std::vector<mint> &x, const std::vector<mint> &y) {
    int n = x.size();
    if (n == 0) return {};
    int m = std::bit_ceil<unsigned>(n);
    auto up = internal_fps::subproduct_tree(x, m);

    // f = (prod (x - x_i))' を各 x_i で評価すると prod_{j!=i}(x_i - x_j) になる。
    std::vector<mint> f = up[1];
    f.erase(f.begin());
    for (int i = 0; i < n; ++i) f[i] *= i + 1;

    // d[i] = f(x_i)。剰余木の下降で全点まとめて評価する (しきい値以下は Horner)。
    std::vector<mint> d(n);
    internal_fps::evaluate_down(up, x, m, n, 1, internal_fps::mod_monic(f, up[1]), d);

    // 葉に y_i / d_i を置き、上に向かって sum g_child * up[sibling] で畳み込んで復元。
    std::vector<std::vector<mint>> g(m << 1);
    for (int i = 0; i < n; ++i) g[m + i] = {y[i] / d[i]};
    for (int i = m; i--;)
        g[i] = plus(internal_fps::conv_auto(g[i << 1 | 0], up[i << 1 | 1]),
                    internal_fps::conv_auto(g[i << 1 | 1], up[i << 1 | 0]));
    return g[1];
}

template <internal::static_modint_c mint>
std::vector<mint> taylor_shift(std::vector<mint> f, mint c) {
    int n = f.size();
    static Combination<mint> comb;
    for (int i = 0; i < n; ++i) f[i] *= comb.fact(i);
    std::reverse(f.begin(), f.end());
    std::vector<mint> g(n);
    mint c_pow = 1;
    for (int i = 0; i < n; ++i) {
        g[i] = c_pow * comb.finv(i);
        c_pow *= c;
    }
    f = convolution(f, g);
    f.resize(n);
    std::reverse(f.begin(), f.end());
    for (int i = 0; i < n; ++i) f[i] *= comb.finv(i);
    return f;
}

}  // namespace fps
