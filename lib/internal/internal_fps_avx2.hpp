#pragma once
#include <algorithm>
#include <bit>
#include <cstdint>
#include <vector>
#include "internal/internal_fft_avx2.hpp"

// Montgomery + AVX2 NTT を土台にした FPS の inv / exp / log。
// 係数はすべて [0, 2*mod) の Montgomery 表現で持ち、変換は internal::avx2::butterfly /
// butterfly_inv をそのまま使う。Newton 法の各段で DFT を可能な限り使い回し、
// 通常の convolution ベース実装より NTT 回数を削減する。
// AVX2 を持たない CPU では未定義動作なので、呼び出し側 (fps) が実行時判定で振り分けること。

#define ALGO_AVX2_TARGET __attribute__((target("avx2")))

namespace internal {
namespace avx2 {

// 2 つの Montgomery バッファのレーンごとの積 (in-place, a *= b)。
// 8 レーン単位で処理し、端数 (n が 8 の倍数でない場合) はスカラで処理する。
template <u32 mod>
ALGO_AVX2_TARGET void hadamard(u32 *a, const u32 *b, int n) {
    using s = mont<mod>;
    static const montx8<mod> v;
    int i = 0;
    for (; i + 8 <= n; i += 8) {
        __m256i x = _mm256_loadu_si256((const __m256i *)(a + i));
        __m256i y = _mm256_loadu_si256((const __m256i *)(b + i));
        _mm256_storeu_si256((__m256i *)(a + i), v.mul(x, y));
    }
    for (; i < n; ++i) a[i] = s::mul(a[i], b[i]);
}

// a を定数 c (Montgomery) でスケールする (in-place)。端数はスカラで処理する。
template <u32 mod>
ALGO_AVX2_TARGET void scale(u32 *a, u32 c, int n) {
    using s = mont<mod>;
    static const montx8<mod> v;
    __m256i vc = _mm256_set1_epi32((int)c);
    int i = 0;
    for (; i + 8 <= n; i += 8) {
        __m256i x = _mm256_loadu_si256((const __m256i *)(a + i));
        _mm256_storeu_si256((__m256i *)(a + i), v.mul(x, vc));
    }
    for (; i < n; ++i) a[i] = s::mul(a[i], c);
}

// 長さ z (2 冪) の逆変換用スケール係数 1/z を Montgomery 表現で返す。
template <u32 mod>
ALGO_AVX2_TARGET u32 inv_len(int z) {
    using s = mont<mod>;
    return s::inv(s::to((u32)z));
}

// 逆変換 + 1/z スケールをまとめて行う (in-place)。長さ z は 8 の倍数を想定。
template <u32 mod>
ALGO_AVX2_TARGET void idft_scaled(u32 *a, int z) {
    butterfly_inv<mod>(a, z);
    scale<mod>(a, inv_len<mod>(z), z);
}

// 1/i (i = 0..n, Montgomery 表現) を O(n) で構築する。inv_tbl[0] は未定義 (0 を入れる)。
// inv[i] = -(mod/i) * inv[mod%i] (mod は素数, i < mod)。
template <u32 mod>
ALGO_AVX2_TARGET std::vector<u32> inv_table(int n) {
    using s = mont<mod>;
    std::vector<u32> r(std::max(2, n + 1));
    r[0] = 0;
    r[1] = s::to(1);
    for (int i = 2; i <= n; ++i) {
        // -(mod/i) * inv[mod%i]
        u32 t = s::mul(r[mod % i], s::to((u32)(mod / i)));
        r[i] = s::sub(0, t);
    }
    return r;
}

// 線形畳み込み a * b (Montgomery 表現入出力, 長さ na+nb-1)。butterfly を直接使う。
template <u32 mod>
ALGO_AVX2_TARGET std::vector<u32> conv(const std::vector<u32> &a, const std::vector<u32> &b) {
    int na = (int)a.size(), nb = (int)b.size();
    if (!na || !nb) return {};
    int z = std::bit_ceil<unsigned>((unsigned)std::max(1, na + nb - 1));
    std::vector<u32> fa(z, 0), fb(z, 0);
    for (int i = 0; i < na; ++i) fa[i] = a[i];
    for (int i = 0; i < nb; ++i) fb[i] = b[i];
    butterfly<mod>(fa.data(), z);
    butterfly<mod>(fb.data(), z);
    hadamard<mod>(fa.data(), fb.data(), z);
    idft_scaled<mod>(fa.data(), z);
    fa.resize(na + nb - 1);
    return fa;
}

// inv: h の逆元を deg 項求める。Newton 法 (g の DFT を 2 度使い回す)。
// 入力 hm は Montgomery 表現の係数列 (長さ >= 1, hm[0] != 0)。戻り値も Montgomery, 長さ deg。
template <u32 mod>
ALGO_AVX2_TARGET std::vector<u32> inv(const std::vector<u32> &hm, int deg) {
    using s = mont<mod>;
    int hn = (int)hm.size();
    std::vector<u32> res(deg, 0);
    res[0] = s::inv(hm[0]);
    for (int d = 1; d < deg; d <<= 1) {
        int z = 2 * d;
        std::vector<u32> f(z, 0), g(z, 0);
        for (int i = 0; i < std::min(hn, z); ++i) f[i] = hm[i];
        for (int i = 0; i < d; ++i) g[i] = res[i];
        butterfly<mod>(g.data(), z);  // g の DFT は 2 度使う
        butterfly<mod>(f.data(), z);
        hadamard<mod>(f.data(), g.data(), z);
        idft_scaled<mod>(f.data(), z);
        for (int i = 0; i < d; ++i) f[i] = 0;  // 上位半分のみ残す
        butterfly<mod>(f.data(), z);
        hadamard<mod>(f.data(), g.data(), z);
        idft_scaled<mod>(f.data(), z);
        for (int i = d; i < std::min(z, deg); ++i) res[i] = s::sub(0, f[i]);
    }
    return res;
}

// log: h の log を deg 項求める。h[0] == 1 が前提。log(h) = ∫ h'/h。
// 入力 hm は Montgomery 表現 (長さ >= 1)。戻り値も Montgomery, 長さ deg。
template <u32 mod>
ALGO_AVX2_TARGET std::vector<u32> log(const std::vector<u32> &hm, int deg) {
    using s = mont<mod>;
    int hn = (int)hm.size();
    std::vector<u32> res(deg, 0);
    if (deg <= 1) return res;
    // 微分 h' (長さ hn-1) と h^{-1} (deg 項) を畳み込み、deg-1 項取って積分する。
    int dn = std::min(hn, deg) - 1;
    if (dn <= 0) return res;
    std::vector<u32> dh(dn);
    for (int i = 0; i < dn; ++i) dh[i] = s::mul(hm[i + 1], s::to((u32)(i + 1)));
    auto ih = inv<mod>(hm, deg);
    int in = (int)ih.size();
    int z = std::bit_ceil<unsigned>((unsigned)std::max(1, dn + in - 1));
    std::vector<u32> a(z, 0), b(z, 0);
    for (int i = 0; i < dn; ++i) a[i] = dh[i];
    for (int i = 0; i < in; ++i) b[i] = ih[i];
    butterfly<mod>(a.data(), z);
    butterfly<mod>(b.data(), z);
    hadamard<mod>(a.data(), b.data(), z);
    idft_scaled<mod>(a.data(), z);
    // 積分: res[i] = a[i-1] / i (i = 1 .. deg-1)
    auto it = inv_table<mod>(deg - 1);
    for (int i = 1; i < deg; ++i) {
        if (i - 1 < z) res[i] = s::mul(a[i - 1], it[i]);
    }
    return res;
}

// exp: h の exp を deg 項求める。h[0] == 0 が前提。
// Newton 法で f = exp(h) と g = f^{-1} を併走させ、DFT(f), DFT(g) を段内で使い回す。
// 入力 hm は Montgomery 表現 (長さ >= 1, hm[0] == 0)。戻り値も Montgomery, 長さ deg。
template <u32 mod>
ALGO_AVX2_TARGET std::vector<u32> exp(const std::vector<u32> &hm, int deg) {
    using s = mont<mod>;
    int hn = (int)hm.size();
    u32 one = s::to(1);
    std::vector<u32> f(deg, 0), g(deg, 0);
    f[0] = one;
    g[0] = one;
    // idx[i] = i, iv[i] = 1/i (Montgomery)。全段で使い回す (添字は最大で z = 2d < 2*deg)。
    int mx = std::max(2, 2 * deg);
    std::vector<u32> idx(mx + 1);
    for (int i = 0; i <= mx; ++i) idx[i] = s::to((u32)i);
    auto iv = inv_table<mod>(mx);
    auto hc = [&](int i) -> u32 { return i < hn ? hm[i] : 0u; };
    auto dhc = [&](int i) -> u32 { return i < hn ? s::mul(hm[i], idx[i]) : 0u; };

    for (int d = 1; d < deg; d <<= 1) {
        int z = 2 * d;
        // dt = h'[0..d) = (h[i]*i)
        std::vector<u32> dt(d);
        for (int i = 0; i < d; ++i) dt[i] = dhc(i);
        std::vector<u32> sf(d), tf(d), tg(d);
        for (int i = 0; i < d; ++i) sf[i] = f[i];
        for (int i = 0; i < d; ++i) tf[i] = f[i];
        for (int i = 0; i < d; ++i) tg[i] = g[i];

        tf = conv<mod>(tf, dt);
        tf.resize(z, 0);
        for (int i = 0; i < d; ++i) tf[i] = s::sub(tf[i], s::mul(f[i], idx[i]));
        tf = conv<mod>(tf, tg);
        tf.resize(z, 0);
        for (int i = 0; i < d; ++i) tf[i] = s::sub(tf[i], dt[i]);
        for (int i = 1; i < z; ++i) tf[i] = s::mul(tf[i], iv[i]);
        tf[0] = 0;
        for (int i = 0; i < std::min(hn, z); ++i) tf[i] = s::add(tf[i], hm[i]);
        tf = conv<mod>(sf, tf);
        for (int i = d; i < std::min(deg, z); ++i) f[i] = tf[i];

        // g を 2d 項へ更新 (Newton inverse, 変換長 z = 2d, gt の DFT を 2 度使い回す)。
        std::vector<u32> ft(z, 0), gt2(z, 0);
        for (int i = 0; i < std::min(z, deg); ++i) ft[i] = f[i];
        for (int i = 0; i < d; ++i) gt2[i] = g[i];
        butterfly<mod>(ft.data(), z);
        butterfly<mod>(gt2.data(), z);
        hadamard<mod>(ft.data(), gt2.data(), z);
        idft_scaled<mod>(ft.data(), z);
        for (int i = 0; i < d; ++i) ft[i] = 0;
        butterfly<mod>(ft.data(), z);
        hadamard<mod>(ft.data(), gt2.data(), z);
        idft_scaled<mod>(ft.data(), z);
        for (int i = d; i < std::min(z, deg); ++i) g[i] = s::sub(0, ft[i]);
        (void)hc;
    }
    return f;
}

// sqrt: g^2 = h を deg 項求める。h[0] != 0 が前提で、定数項の平方根 g[0] を g0 (Montgomery) で渡す。
// Newton 法で g = sqrt(h) と h_inv = g^{-1} を併走させ、DFT(h_inv) を段内で 2 度使い回す。
// 入力 hm は Montgomery 表現 (長さ >= 1)。戻り値も Montgomery, 長さ deg。
template <u32 mod>
ALGO_AVX2_TARGET std::vector<u32> sqrt(const std::vector<u32> &hm, int deg, u32 g0) {
    using s = mont<mod>;
    int hn = (int)hm.size();
    u32 inv2 = s::inv(s::to(2));
    std::vector<u32> g(deg, 0), hi(deg, 0);  // g = sqrt(h), hi = g^{-1}
    g[0] = g0;
    hi[0] = s::inv(g0);
    auto hc = [&](int i) -> u32 { return i < hn ? hm[i] : 0u; };
    for (int d = 1; d < deg; d <<= 1) {
        int z = 2 * d;
        // sq = g^2 mod x^z
        std::vector<u32> sq(z, 0);
        for (int i = 0; i < d; ++i) sq[i] = g[i];
        butterfly<mod>(sq.data(), z);
        hadamard<mod>(sq.data(), sq.data(), z);
        idft_scaled<mod>(sq.data(), z);
        // e = (h - g^2) は x^d で割り切れる。e * hi の [d, z) が g の新しい項 (× 1/2)。
        std::vector<u32> e(z, 0);
        for (int i = d; i < z; ++i) e[i] = s::sub(hc(i), sq[i]);
        std::vector<u32> ht(z, 0);  // DFT(hi) は逆元更新でも再利用する
        for (int i = 0; i < d; ++i) ht[i] = hi[i];
        butterfly<mod>(ht.data(), z);
        butterfly<mod>(e.data(), z);
        hadamard<mod>(e.data(), ht.data(), z);
        idft_scaled<mod>(e.data(), z);
        for (int i = d; i < std::min(z, deg); ++i) g[i] = s::mul(inv2, e[i]);
        if (z >= deg) break;  // これ以上 hi を伸ばす必要はない
        // hi を 2d 項へ更新 (Newton inverse, DFT(hi) を再利用)。
        std::vector<u32> gt(z, 0);
        for (int i = 0; i < z; ++i) gt[i] = g[i];
        butterfly<mod>(gt.data(), z);
        hadamard<mod>(gt.data(), ht.data(), z);
        idft_scaled<mod>(gt.data(), z);
        for (int i = 0; i < d; ++i) gt[i] = 0;
        butterfly<mod>(gt.data(), z);
        hadamard<mod>(gt.data(), ht.data(), z);
        idft_scaled<mod>(gt.data(), z);
        for (int i = d; i < z; ++i) hi[i] = s::sub(0, gt[i]);
    }
    return g;
}

}  // namespace avx2
}  // namespace internal

#undef ALGO_AVX2_TARGET
