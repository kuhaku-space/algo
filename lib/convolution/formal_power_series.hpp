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
#include "number_theory/sqrt.hpp"

/// @file
/// @brief 形式的冪級数 (FPS)
/// @details modint 係数の形式的冪級数を `std::vector<mint>` (index i = x^i の係数) で表し、
///          四則・inv / log / exp / pow / sqrt / composition /
///          compositional_inverse・多項式除算・多点評価・補間・Taylor shift を提供する。 NTT-friendly な mod < 2^30
///          かつ実行時 AVX2 対応 CPU では inv / log / exp を Montgomery + AVX2 NTT 実装に自動で振り分ける。

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

// 前進 NTT (ACL butterfly, スケーリング無し)。
template <internal::static_modint_c mint>
void ntt(std::vector<mint> &v) {
    internal::butterfly(v);
}

// 逆 NTT + 1/n スケーリング (intt)。
template <internal::static_modint_c mint>
void intt(std::vector<mint> &v) {
    internal::butterfly_inv(v);
    mint c = mint((int)v.size()).inv();
    for (auto &e : v) e *= c;
}

}  // namespace internal_fps

/// @brief 形式的冪級数の加算
/// @tparam mint static modint
/// @param f 係数列
/// @param g 係数列
/// @return std::vector<mint> f + g (長さ max(f.size(), g.size()))
template <internal::static_modint_c mint>
std::vector<mint> plus(const std::vector<mint> &f, const std::vector<mint> &g) {
    int n = f.size(), m = g.size();
    int s = std::max(n, m);
    std::vector<mint> res = f;
    res.resize(s);
    for (int i = 0; i < m; ++i) res[i] += g[i];
    return res;
}

/// @brief 逆元 1 / h (mod x^deg)
/// @details ニュートン法で deg 項まで求める。定数項 h[0] は逆元を持つ必要がある。
///          条件を満たせば Montgomery + AVX2 NTT 実装へ振り分ける。
/// @tparam mint static modint
/// @param h 係数列 (h[0] != 0 が必要)
/// @param deg 求める項数
/// @return std::vector<mint> h * res ≡ 1 (mod x^deg) を満たす res (長さ deg)
/// @note 計算量 O(deg log deg)
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

/// @brief 逆元 1 / h (deg は h.size())
/// @tparam mint static modint
/// @param h 係数列 (h[0] != 0 が必要)
/// @return std::vector<mint> 長さ h.size() の逆元
template <internal::static_modint_c mint>
std::vector<mint> inv(const std::vector<mint> &h) {
    return inv(h, h.size());
}

/// @brief 対数 log h (mod x^deg)
/// @details log h = ∫ h' / h dx で求める。定数項 h[0] == 1 が必要。
///          条件を満たせば Montgomery + AVX2 NTT 実装へ振り分ける。
/// @tparam mint static modint
/// @param h 係数列 (h[0] == 1 が必要)
/// @param deg 求める項数
/// @return std::vector<mint> log h (長さ deg, 定数項は 0)
/// @note 計算量 O(deg log deg)
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

/// @brief 対数 log h (deg は h.size())
/// @tparam mint static modint
/// @param h 係数列 (h[0] == 1 が必要)
/// @return std::vector<mint> 長さ h.size() の log h
template <internal::static_modint_c mint>
std::vector<mint> log(const std::vector<mint> &h) {
    return log(h, h.size());
}

/// @brief 指数 exp h (mod x^deg)
/// @details ニュートン法で求める。定数項 h[0] == 0 が必要。
///          条件を満たせば Montgomery + AVX2 NTT 実装へ振り分ける。
/// @tparam mint static modint
/// @param h 係数列 (h[0] == 0 が必要)
/// @param deg 求める項数
/// @return std::vector<mint> exp h (長さ deg, 定数項は 1)
/// @note 計算量 O(deg log deg)
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

/// @brief 指数 exp h (deg は h.size())
/// @tparam mint static modint
/// @param h 係数列 (h[0] == 0 が必要)
/// @return std::vector<mint> 長さ h.size() の exp h
template <internal::static_modint_c mint>
std::vector<mint> exp(const std::vector<mint> &h) {
    return exp(h, h.size());
}

/// @brief 冪乗 h^m (mod x^deg)
/// @details 最低次の項 c x^k を括り出し pow = exp(m log(h / (c x^k))) * c^m * x^{k m} で求める。
///          m が負なら h^{|m|} の逆元を返す (h[0] != 0 が必要)。最低次が x^k のとき x^{k m} が
///          deg 以上に押し出される場合や全係数 0 の場合は全 0 を返す。
/// @tparam mint static modint
/// @param h 係数列
/// @param m 指数 (負も可)
/// @param deg 求める項数
/// @return std::vector<mint> h^m (長さ deg)。m == 0 は定数 1 を返す
/// @note 計算量 O(deg log deg)
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

/// @brief 冪乗 h^m (deg は h.size())
/// @tparam mint static modint
/// @param h 係数列
/// @param m 指数 (負も可)
/// @return std::vector<mint> 長さ h.size() の h^m
template <internal::static_modint_c mint>
std::vector<mint> pow(const std::vector<mint> &h, std::int64_t m) {
    return pow(h, m, h.size());
}

/// @brief 平方根 sqrt h (mod x^deg)
/// @details g^2 ≡ h (mod x^deg) を満たす g を求める。最低次の項 c x^k を括り出し、
///          k が偶数かつ c が平方剰余のとき g = x^{k/2} sqrt(h / x^k) をニュートン法で求める。
///          ニュートン法は g = sqrt と g^{-1} を併走させ各段で DFT を使い回す
///          (full inverse の再計算を避ける)。条件を満たせば Montgomery + AVX2 NTT 実装へ振り分ける。
///          k が奇数、または c が平方非剰余で解が存在しない場合は空列を返す。
/// @tparam mint static modint
/// @param h 係数列
/// @param deg 求める項数
/// @return std::vector<mint> g^2 ≡ h を満たす g (長さ deg)。解なしのときは空列
/// @note 計算量 O(deg log deg)
template <internal::static_modint_c mint>
std::vector<mint> sqrt(const std::vector<mint> &h, int deg) {
    int n = h.size();
    int k = 0;
    while (k < n && h[k] == 0) ++k;
    if (k == n) return std::vector<mint>(deg);  // h ≡ 0 → sqrt は全 0
    if (k & 1) return {};                       // 最低次が奇数 → 解なし
    if (!has_sqrt_mod(h[k])) return {};         // 定数項が平方非剰余 → 解なし
    // h = x^k (h[k] + ...), sqrt(h) = x^{k/2} sqrt(h >> k)。
    int shift = k / 2;
    if (shift >= deg) return std::vector<mint>(deg);
    int core_deg = deg - shift;
    std::vector<mint> f(h.begin() + k, h.end());
    mint g0 = sqrt_mod(f[0]);

    std::vector<mint> g;
    constexpr unsigned int mod = (unsigned int)mint::mod();
    if constexpr (mod < (1u << 30)) {
        if (internal_fps::use_avx2<mint>()) {
            using mt = internal::avx2::mont<mod>;
            g = internal_fps::from_mont<mint>(
                internal::avx2::sqrt<mod>(internal_fps::to_mont(f), core_deg, mt::to((std::uint32_t)g0.val())));
            g.insert(g.begin(), shift, mint());
            return g;
        }
    }
    // 通常版: g = sqrt(f) と hi = g^{-1} を併走させ、各段で DFT(hi) を使い回すニュートン法。
    g.assign(core_deg, mint());
    std::vector<mint> hi(core_deg, mint());
    g[0] = g0;
    hi[0] = g0.inv();
    mint inv2 = mint(2).inv();
    auto fc = [&](int i) { return i < (int)f.size() ? f[i] : mint(); };
    for (int d = 1; d < core_deg; d <<= 1) {
        int z = 2 * d;
        mint iz = mint(z).inv();
        // sq = g^2 mod x^z
        std::vector<mint> sq(z);
        for (int i = 0; i < d; ++i) sq[i] = g[i];
        internal::butterfly(sq);
        for (int i = 0; i < z; ++i) sq[i] *= sq[i];
        internal::butterfly_inv(sq);
        for (int i = 0; i < z; ++i) sq[i] *= iz;
        // e = (f - g^2) は x^d で割り切れる。e * hi の [d, z) が g の新しい項 (× 1/2)。
        std::vector<mint> e(z), ht(z);
        for (int i = d; i < z; ++i) e[i] = fc(i) - sq[i];
        for (int i = 0; i < d; ++i) ht[i] = hi[i];
        internal::butterfly(ht);  // DFT(hi) は逆元更新でも再利用する
        internal::butterfly(e);
        for (int i = 0; i < z; ++i) e[i] *= ht[i];
        internal::butterfly_inv(e);
        for (int i = 0; i < z; ++i) e[i] *= iz;
        for (int i = d; i < std::min(z, core_deg); ++i) g[i] = inv2 * e[i];
        if (z >= core_deg) break;  // これ以上 hi を伸ばす必要はない
        // hi を 2d 項へ更新 (Newton inverse, DFT(hi) を再利用)。
        std::vector<mint> gt(z);
        for (int i = 0; i < z; ++i) gt[i] = g[i];
        internal::butterfly(gt);
        for (int i = 0; i < z; ++i) gt[i] *= ht[i];
        internal::butterfly_inv(gt);
        for (int i = 0; i < z; ++i) gt[i] *= iz;
        for (int i = 0; i < d; ++i) gt[i] = 0;
        internal::butterfly(gt);
        for (int i = 0; i < z; ++i) gt[i] *= ht[i];
        internal::butterfly_inv(gt);
        for (int i = 0; i < z; ++i) gt[i] *= iz;
        for (int i = d; i < z; ++i) hi[i] = -gt[i];
    }
    g.resize(core_deg);
    g.insert(g.begin(), shift, mint());
    return g;
}

/// @brief 平方根 sqrt h (deg は h.size())
/// @tparam mint static modint
/// @param h 係数列
/// @return std::vector<mint> 長さ h.size() の sqrt h。解なしのときは空列
template <internal::static_modint_c mint>
std::vector<mint> sqrt(const std::vector<mint> &h) {
    return sqrt(h, h.size());
}

namespace internal_fps {

// Kinoshita-Suzuki の power projection。[x^n] g(x) f(x)^i を i = 0..m で列挙して返す。
// n = f.size()-1。g は f^i に掛ける重み多項式 (既定 g = 1)。m == -1 のときは m = n。
// f[0] == 0 のときは多項式版 (S.rev())、そうでなければ有理式版 (S/(T+x^k) の rev) を返す。
// @see https://nyaannyaan.github.io/library/fps/pow-enumerate.hpp
// @note 計算量 O(n log^2 n)
template <internal::static_modint_c mint>
std::vector<mint> pow_enumerate(std::vector<mint> f, std::vector<mint> g, int m) {
    using std::begin;
    using std::end;
    using fps_t = std::vector<mint>;
    int n = (int)f.size() - 1, k = 1;
    g.resize(n + 1);
    if (m == -1) m = n;
    int h = 1;
    while (h < n + 1) h *= 2;
    fps_t P((n + 1) * k), Q((n + 1) * k), nP, nQ, buf, buf2;
    for (int i = 0; i <= n; i++) P[i * k + 0] = g[i];
    for (int i = 0; i <= n; i++) Q[i * k + 0] = -f[i];
    Q[0] += 1;
    while (n) {
        mint inv2 = mint(2).inv();
        mint w = mint(internal::primitive_root<mint::mod()>).pow((mint::mod() - 1) / (2 * k));
        buf2.resize(k);
        auto ntt_doubling = [&]() {
            std::copy(begin(buf), end(buf), begin(buf2));
            intt(buf2);
            mint c = 1;
            for (int i = 0; i < k; i++) buf2[i] *= c, c *= w;
            ntt(buf2);
            std::copy(begin(buf2), end(buf2), std::back_inserter(buf));
        };
        nP.clear(), nQ.clear();
        for (int i = 0; i <= n; i++) {
            buf.resize(k);
            std::copy(begin(P) + i * k, begin(P) + (i + 1) * k, begin(buf));
            ntt_doubling();
            std::copy(begin(buf), end(buf), std::back_inserter(nP));
            buf.resize(k);
            std::copy(begin(Q) + i * k, begin(Q) + (i + 1) * k, begin(buf));
            if (i == 0) {
                for (int j = 0; j < k; j++) buf[j] -= 1;
                ntt_doubling();
                for (int j = 0; j < k; j++) buf[j] += 1;
                for (int j = 0; j < k; j++) buf[k + j] -= 1;
            } else {
                ntt_doubling();
            }
            std::copy(begin(buf), end(buf), std::back_inserter(nQ));
        }
        nP.resize(2 * h * 2 * k);
        nQ.resize(2 * h * 2 * k);
        fps_t p(2 * h), q(2 * h);
        w = mint(internal::primitive_root<mint::mod()>).pow((mint::mod() - 1) / (2 * h));
        mint iw = w.inv();
        std::vector<int> btr;
        if (n % 2) {
            btr.resize(h);
            for (int i = 0, lg = std::countr_zero<unsigned>((unsigned)h); i < h; i++)
                btr[i] = (btr[i >> 1] >> 1) + ((i & 1) << (lg - 1));
        }
        for (int j = 0; j < 2 * k; j++) {
            p.assign(2 * h, 0);
            q.assign(2 * h, 0);
            for (int i = 0; i < h; i++) { p[i] = nP[i * 2 * k + j], q[i] = nQ[i * 2 * k + j]; }
            ntt(p), ntt(q);
            for (int i = 0; i < 2 * h; i += 2) std::swap(q[i], q[i + 1]);
            for (int i = 0; i < 2 * h; i++) p[i] *= q[i];
            for (int i = 0; i < h; i++) q[i] = q[i * 2] * q[i * 2 + 1];
            if (n % 2 == 0) {
                for (int i = 0; i < h; i++) p[i] = (p[i * 2] + p[i * 2 + 1]) * inv2;
            } else {
                mint c = inv2;
                buf.resize(h);
                for (int i : btr) buf[i] = (p[i * 2] - p[i * 2 + 1]) * c, c *= iw;
                std::swap(p, buf);
            }
            p.resize(h), q.resize(h);
            intt(p), intt(q);
            for (int i = 0; i < h; i++) nP[i * 2 * k + j] = p[i];
            for (int i = 0; i < h; i++) nQ[i * 2 * k + j] = q[i];
        }
        nP.resize((n / 2 + 1) * 2 * k);
        nQ.resize((n / 2 + 1) * 2 * k);
        std::swap(P, nP), std::swap(Q, nQ);
        n /= 2, h /= 2, k *= 2;
    }
    fps_t S{begin(P), begin(P) + k};
    fps_t T{begin(Q), begin(Q) + k};
    intt(S), intt(T);
    T[0] -= 1;
    std::reverse(S.begin(), S.end());
    if (f[0] == 0) {
        S.resize(m + 1);
        return S;
    }
    // (T + x^k).rev() の逆元を掛ける。
    fps_t den = T;
    den.resize(k + 1);
    den[k] += 1;
    std::reverse(den.begin(), den.end());
    std::vector<mint> res = convolution(S, fps::inv(den, m + 1));
    res.resize(m + 1);
    return res;
}

}  // namespace internal_fps

/// @brief 合成 (composition) f(g(x)) (mod x^deg)
/// @details h(x) = f(g(x)) = Σ f[i] g(x)^i (mod x^deg) を Kinoshita-Suzuki の分割統治で求める。
///          Nyaan の composition は g(f(x)) を返すため f と g を入れ替えて呼び出す。
///          f は多項式として扱うため g[0] != 0 でも正しく計算できる。
/// @tparam mint static modint
/// @param f 外側の係数列
/// @param g 内側の係数列
/// @param deg 求める項数
/// @return std::vector<mint> f(g(x)) (長さ deg)
/// @see https://nyaannyaan.github.io/library/fps/fps-composition.hpp
/// @note 計算量 O(deg log^2 deg)
template <internal::static_modint_c mint>
std::vector<mint> composition(const std::vector<mint> &outer, const std::vector<mint> &inner, int deg) {
    using fps_t = std::vector<mint>;
    if (deg <= 0) return std::vector<mint>(std::max(deg, 0), mint());
    // Nyaan composition(f, g) は g(f(x)) を返すので、ここでは f = inner, g = outer とする
    // (= outer(inner(x)))。
    std::vector<mint> f = inner;
    std::vector<mint> g = outer;
    auto dfs = [&](auto rc, fps_t Q, int n, int hh, int kk) -> fps_t {
        if (n == 0) {
            fps_t T{Q.begin(), Q.begin() + kk};
            T.push_back(1);
            std::reverse(T.begin(), T.end());
            fps_t Ti = fps::inv(T);
            std::reverse(Ti.begin(), Ti.end());
            fps_t u = convolution(g, Ti);
            fps_t P(hh * kk);
            for (int i = 0; i < (int)g.size(); i++) {
                if (i + kk < (int)u.size()) P[kk - 1 - i] = u[i + kk];
            }
            return P;
        }
        fps_t nQ(4 * hh * kk), nR(2 * hh * kk);
        for (int i = 0; i < kk; i++) std::copy(Q.begin() + i * hh, Q.begin() + i * hh + n + 1, nQ.begin() + i * 2 * hh);
        nQ[kk * 2 * hh] += 1;
        internal_fps::ntt(nQ);
        for (int i = 0; i < 4 * hh * kk; i += 2) std::swap(nQ[i], nQ[i + 1]);
        for (int i = 0; i < 2 * hh * kk; i++) nR[i] = nQ[i * 2] * nQ[i * 2 + 1];
        internal_fps::intt(nR);
        nR[0] -= 1;
        Q.assign(hh * kk, 0);
        for (int i = 0; i < 2 * kk; i++)
            for (int j = 0; j <= n / 2; j++) Q[i * hh / 2 + j] = nR[i * hh + j];
        auto P = rc(rc, Q, n / 2, hh / 2, kk * 2);
        fps_t nP(4 * hh * kk);
        for (int i = 0; i < 2 * kk; i++)
            for (int j = 0; j <= n / 2; j++) nP[i * 2 * hh + j * 2 + n % 2] = P[i * hh / 2 + j];
        internal_fps::ntt(nP);
        for (int i = 1; i < 4 * hh * kk; i *= 2) std::reverse(nQ.begin() + i, nQ.begin() + i * 2);
        for (int i = 0; i < 4 * hh * kk; i++) nP[i] *= nQ[i];
        internal_fps::intt(nP);
        P.assign(hh * kk, 0);
        for (int i = 0; i < kk; i++)
            std::copy(nP.begin() + i * 2 * hh, nP.begin() + i * 2 * hh + n + 1, P.begin() + i * hh);
        return P;
    };
    // 出力は mod x^deg だが、g[0] != 0 のとき高次の f[i] も低次へ寄与する。Nyaan の枠組みは
    // n = f.size()-1 項を計算するため、内部の計算項数を max(deg, f.size(), g.size()) に揃えてから
    // 先頭 deg 項を返す。
    int work = std::max({deg, (int)f.size(), (int)g.size()});
    f.resize(work), g.resize(work);
    int n = (int)f.size() - 1, k = 1;
    int h = 1;
    while (h < n + 1) h *= 2;
    fps_t Q(h * k);
    for (int i = 0; i <= n; i++) Q[i] = -f[i];
    fps_t P = dfs(dfs, Q, n, h, k);
    P.resize(n + 1);
    std::reverse(P.begin(), P.end());
    P.resize(deg);
    return P;
}

/// @brief 合成 (composition) f(g(x)) (deg は max(f.size(), g.size()))
/// @tparam mint static modint
/// @param f 外側の係数列
/// @param g 内側の係数列
/// @return std::vector<mint> f(g(x))
template <internal::static_modint_c mint>
std::vector<mint> composition(const std::vector<mint> &f, const std::vector<mint> &g) {
    return composition(f, g, std::max(f.size(), g.size()));
}

/// @brief 合成逆 (compositional inverse) g (mod x^deg)
/// @details f(g(x)) = g(f(x)) = x (mod x^deg) を満たす g を求める。f[0] == 0 かつ f[1] != 0 が前提。
///          Kinoshita-Suzuki の power projection (pow_enumerate) で [x^n] f(x)^k を列挙し、
///          Lagrange-Bürmann 反転 g = (n^{-1} log(rev(h)/h0))^{-1} の exp で復元する
///          (h_k = n [x^k] (列挙結果) / k)。
/// @tparam mint static modint
/// @param f 係数列 (f[0] == 0, f[1] != 0 が必要)
/// @param deg 求める項数
/// @return std::vector<mint> g(x) (長さ deg, g[0] == 0)
/// @see https://nyaannyaan.github.io/library/fps/compositional-inverse.hpp
/// @note 計算量 O(deg log^2 deg)
template <internal::static_modint_c mint>
std::vector<mint> compositional_inverse(const std::vector<mint> &f, int deg) {
    assert(deg <= 0 || f.empty() || f[0] == 0);
    assert((int)f.size() < 2 || f[1] != 0);
    if (deg <= 0) return std::vector<mint>(std::max(deg, 0), mint());
    if (deg == 1) return std::vector<mint>(1, mint());
    if (deg < 2) return std::vector<mint>(deg, mint());
    int n = deg - 1;
    // h = pow_enumerate(f) * n。pow_enumerate は n = f.size()-1 を使うため f を deg 項に揃える。
    std::vector<mint> ff = f;
    ff.resize(deg);
    std::vector<mint> h = internal_fps::pow_enumerate(ff, std::vector<mint>{mint(1)}, -1);
    h.resize(n + 1);
    for (auto &e : h) e *= n;
    for (int k = 1; k <= n; ++k) h[k] /= k;
    std::reverse(h.begin(), h.end());
    mint h0i = h[0].inv();
    for (auto &e : h) e *= h0i;  // h *= h[0]^{-1} (h[0] == 1)
    std::vector<mint> lg = log(h);
    mint c = mint(-n).inv();
    for (auto &e : lg) e *= c;
    std::vector<mint> g = exp(lg);
    mint f1i = f[1].inv();
    for (auto &e : g) e *= f1i;
    g.insert(g.begin(), mint(0));  // g << 1
    g.resize(deg);
    return g;
}

/// @brief 合成逆 (compositional inverse) g (deg は f.size())
/// @tparam mint static modint
/// @param f 係数列 (f[0] == 0, f[1] != 0 が必要)
/// @return std::vector<mint> 長さ f.size() の g(x)
template <internal::static_modint_c mint>
std::vector<mint> compositional_inverse(const std::vector<mint> &f) {
    return compositional_inverse(f, f.size());
}

/// @brief 多項式の除算 (商と剰余)
/// @details f = q * g + r を満たす商 q と剰余 r (deg r < deg g) を求める。
///          反転して逆元を掛ける標準的な手法。f, g の末尾 0 は内部で除去する。
/// @tparam mint static modint
/// @param f 被除多項式の係数列
/// @param g 除多項式の係数列 (0 多項式でないこと)
/// @return std::pair<商 q, 剰余 r> (どちらも末尾 0 を含まない)
/// @note 計算量 O(n log n) (n = deg f)
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

/// @brief 多項式の商 f / g
/// @tparam mint static modint
/// @param f 被除多項式の係数列
/// @param g 除多項式の係数列 (0 多項式でないこと)
/// @return std::vector<mint> 商 q
template <internal::static_modint_c mint>
std::vector<mint> div(const std::vector<mint> &f, const std::vector<mint> &g) {
    return div_mod(f, g).first;
}

/// @brief 多項式の剰余 f mod g
/// @tparam mint static modint
/// @param f 被除多項式の係数列
/// @param g 除多項式の係数列 (0 多項式でないこと)
/// @return std::vector<mint> 剰余 r (deg r < deg g)
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

/// @brief 多点評価
/// @details 部分積木を構築し剰余木を下降して、f を各点 x_i で同時に評価する。
///          点数が少ない部分木は Horner 法に切り替えて NTT の定数倍を避ける。
/// @tparam mint static modint
/// @param f 評価する多項式の係数列
/// @param x 評価する点の列
/// @return std::vector<mint> f(x_i) の列 (長さ x.size())
/// @note 計算量 O(n log^2 n) (n = max(deg f, |x|))
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

/// @brief 多項式補間 (ラグランジュ補間)
/// @details 相異なる点 (x_i, y_i) を通る次数 n-1 以下の多項式を求める。部分積木を多点評価と
///          共有し、葉に y_i / f'(x_i) を置いて上向きに畳み込んで復元する。x_i は相異なること。
/// @tparam mint static modint
/// @param x 評価点の列 (相異なる)
/// @param y 各点での値の列 (x と同じ長さ)
/// @return std::vector<mint> f(x_i) = y_i を満たす係数列 (長さ x.size())
/// @note 計算量 O(n log^2 n) (n = |x|)
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

/// @brief Taylor shift (係数の平行移動)
/// @details f(x) の係数から g(x) = f(x + c) の係数を求める。f[i] に i! を掛けて反転し、
///          c^j / j! との畳み込みの中央部を取り出す標準的な手法。
/// @tparam mint static modint
/// @param f 係数列 f(x)
/// @param c シフト量
/// @return std::vector<mint> f(x + c) の係数列 (f と同じ長さ)
/// @note 計算量 O(n log n) (n = f.size())
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
