#pragma once
#include <array>
#include <bit>
#include <cstdint>
#include <vector>
#include "internal/internal_math.hpp"
#include "internal/internal_type_traits.hpp"
#include "math/modint.hpp"

// Montgomery 表現 + AVX2 による NTT。NTT-friendly な 32bit 素数 mod 専用。
// 値は [0, 2*mod) の Montgomery 表現で持ち、加減算では完全正規化しない (遅延簡約)。
// 簡約は [0, 2*mod) を返し、最終出力でのみ [0, mod) に正規化する。
// AVX2 命令を使う関数には target("avx2") を付け、TU 全体を -mavx2 で組まなくても
// (競プロジャッジの既定フラグでも) コンパイル・実行できるようにする。
// AVX2 を持たない CPU で実行すると未定義動作なので、呼び出し側 (ntt_avx2.hpp) が
// __AVX2__ または実行時判定で振り分けること。
// @see https://tayu0110.hatenablog.com/entry/2023/05/06/023244

#include <immintrin.h>

#define ALGO_AVX2_TARGET __attribute__((target("avx2")))

namespace internal {
namespace avx2 {

using u32 = std::uint32_t;
using u64 = std::uint64_t;

// スカラ Montgomery (前計算・端数レーン処理用)。mod は 2 < mod < 2^30 の素数を想定。
template <u32 mod>
struct mont {
    static constexpr u32 calc_ninv() {
        u32 inv = mod;
        for (int i = 0; i < 4; ++i) inv *= 2u - mod * inv;
        return inv;  // mod^{-1} mod 2^32
    }
    static constexpr u32 ninv = calc_ninv();
    static constexpr u32 r2 = (u32)(((__uint128_t)1 << 64) % mod);  // (2^64) mod mod

    // 簡約: t < 2^32 * 2*mod を t * 2^-32 mod mod へ写す。出力は [0, 2*mod)。
    static constexpr u32 reduce(u64 t) {
        u32 m = (u32)t * (0u - ninv);
        return (u32)((t + (u64)m * mod) >> 32);
    }
    static constexpr u32 to(u32 a) { return reduce((u64)a * r2); }  // 通常 -> Montgomery
    static constexpr u32 from(u32 a) {
        u32 r = reduce((u64)a);
        return r >= mod ? r - mod : r;
    }
    static constexpr u32 mul(u32 a, u32 b) { return reduce((u64)a * b); }
    static constexpr u32 add(u32 a, u32 b) {
        u32 z = a + b;
        return z >= 2 * mod ? z - 2 * mod : z;
    }
    static constexpr u32 sub(u32 a, u32 b) {
        u32 z = a + 2 * mod - b;
        return z >= 2 * mod ? z - 2 * mod : z;
    }
    static constexpr u32 pow(u32 a, u64 n) {  // a, 戻り値とも Montgomery 表現
        u32 r = to(1);
        while (n) {
            if (n & 1) r = mul(r, a);
            a = mul(a, a);
            n >>= 1;
        }
        return r;
    }
    static constexpr u32 inv(u32 a) { return pow(a, mod - 2); }
};

// AVX2 8 レーン (u32x8) の Montgomery 演算。すべて [0, 2*mod) を保つ。
template <u32 mod>
struct montx8 {
    using s = mont<mod>;
    __m256i mod_, mod2_, ninv_;
    ALGO_AVX2_TARGET montx8()
        : mod_(_mm256_set1_epi32((int)mod)), mod2_(_mm256_set1_epi32((int)(mod * 2))),
          // reduce では m = (u32)t * (-mod^{-1}) を使うので負の逆元を持つ。
          ninv_(_mm256_set1_epi32((int)(0u - s::ninv))) {}

    // 64bit レーンの Montgomery 簡約。t < 2^32 * 2*mod を t*2^-32 mod mod へ (各 64bit の下位)。
    // ラムダだと target 属性を継承しないため (always_inline 失敗)、メンバ関数にしている。
    ALGO_AVX2_TARGET inline __m256i reduce64(__m256i t) const {
        __m256i m = _mm256_mul_epu32(t, ninv_);                 // (lo32(t) * -ninv) の 64bit, 下位 32bit が m
        __m256i mm = _mm256_mul_epu32(m, mod_);                 // m * mod
        return _mm256_srli_epi64(_mm256_add_epi64(t, mm), 32);  // (t + m*mod) >> 32, [0,2*mod)
    }
    ALGO_AVX2_TARGET inline __m256i mul(__m256i a, __m256i b) const {
        // 偶レーン (0,2,4,6) と奇レーン (1,3,5,7) に分けて 64bit 積を作り簡約する。
        __m256i pe = _mm256_mul_epu32(a, b);
        __m256i po = _mm256_mul_epu32(_mm256_srli_epi64(a, 32), _mm256_srli_epi64(b, 32));
        __m256i re = reduce64(pe), ro = reduce64(po);
        ro = _mm256_slli_epi64(ro, 32);
        return _mm256_blend_epi32(re, ro, 0b10101010);
    }
    ALGO_AVX2_TARGET inline __m256i add(__m256i a, __m256i b) const {
        __m256i s = _mm256_add_epi32(a, b);
        return _mm256_min_epu32(s, _mm256_sub_epi32(s, mod2_));
    }
    ALGO_AVX2_TARGET inline __m256i sub(__m256i a, __m256i b) const {
        __m256i s = _mm256_sub_epi32(_mm256_add_epi32(a, mod2_), b);
        return _mm256_min_epu32(s, _mm256_sub_epi32(s, mod2_));
    }
};

// 純 radix-2 DIF/DIT 用の twiddle (rate2/irate2)。下位 3 段は shuffle 化するため
// radix-4 の rate3 系は不要。
template <u32 mod, int g = internal::primitive_root<(int)mod>>
struct fft_info {
    using s = mont<mod>;
    static constexpr int rank2 = std::countr_zero<unsigned>(mod - 1);
    std::array<u32, rank2 + 1> root, iroot;  // Montgomery 表現
    std::array<u32, std::max(0, rank2 - 1)> rate2, irate2;
    fft_info() {
        root[rank2] = s::pow(s::to(g), (mod - 1) >> rank2);
        iroot[rank2] = s::inv(root[rank2]);
        for (int i = rank2 - 1; i >= 0; --i) {
            root[i] = s::mul(root[i + 1], root[i + 1]);
            iroot[i] = s::mul(iroot[i + 1], iroot[i + 1]);
        }
        u32 prod = s::to(1), iprod = s::to(1);
        for (int i = 0; i <= rank2 - 2; ++i) {
            rate2[i] = s::mul(root[i + 2], prod);
            irate2[i] = s::mul(iroot[i + 2], iprod);
            prod = s::mul(prod, iroot[i + 2]);
            iprod = s::mul(iprod, root[i + 2]);
        }
    }
};

// 8 要素ブロック内 DIF: p=4,2,1 をレーン内 shuffle で処理 (順変換の下位 3 段)。
// tw4/tw2/tw1 はそのブロックの twiddle ベクトル (Montgomery)。
template <u32 mod>
ALGO_AVX2_TARGET inline __m256i tail_block(__m256i x, __m256i tw4, __m256i tw2, __m256i tw1, const montx8<mod> &v) {
    // p=4: ペア (i, i+4)
    __m256i lo = _mm256_permute2x128_si256(x, x, 0x00);
    __m256i hi = _mm256_permute2x128_si256(x, x, 0x11);
    __m256i r = v.mul(hi, tw4);
    x = _mm256_permute2x128_si256(v.add(lo, r), v.sub(lo, r), 0x20);
    // p=2: ペア (i, i+2)
    __m256i lo2 = _mm256_shuffle_epi32(x, _MM_SHUFFLE(1, 0, 1, 0));
    __m256i hi2 = _mm256_shuffle_epi32(x, _MM_SHUFFLE(3, 2, 3, 2));
    __m256i r2 = v.mul(hi2, tw2);
    x = _mm256_blend_epi32(v.add(lo2, r2), v.sub(lo2, r2), 0b11001100);
    // p=1: ペア (i, i+1)
    __m256i lo1 = _mm256_shuffle_epi32(x, _MM_SHUFFLE(2, 2, 0, 0));
    __m256i hi1 = _mm256_shuffle_epi32(x, _MM_SHUFFLE(3, 3, 1, 1));
    __m256i r1 = v.mul(hi1, tw1);
    return _mm256_blend_epi32(v.add(lo1, r1), v.sub(lo1, r1), 0b10101010);
}

// 8 要素ブロック内 DIT: p=1,2,4 (逆変換の上位 3 段)。(lo-r) に twiddle を掛ける。
template <u32 mod>
ALGO_AVX2_TARGET inline __m256i tail_block_inv(__m256i x, __m256i tw1, __m256i tw2, __m256i tw4, const montx8<mod> &v) {
    // p=1
    __m256i lo1 = _mm256_shuffle_epi32(x, _MM_SHUFFLE(2, 2, 0, 0));
    __m256i hi1 = _mm256_shuffle_epi32(x, _MM_SHUFFLE(3, 3, 1, 1));
    x = _mm256_blend_epi32(v.add(lo1, hi1), v.mul(v.sub(lo1, hi1), tw1), 0b10101010);
    // p=2
    __m256i lo2 = _mm256_shuffle_epi32(x, _MM_SHUFFLE(1, 0, 1, 0));
    __m256i hi2 = _mm256_shuffle_epi32(x, _MM_SHUFFLE(3, 2, 3, 2));
    x = _mm256_blend_epi32(v.add(lo2, hi2), v.mul(v.sub(lo2, hi2), tw2), 0b11001100);
    // p=4
    __m256i lo = _mm256_permute2x128_si256(x, x, 0x00);
    __m256i hi = _mm256_permute2x128_si256(x, x, 0x11);
    return _mm256_permute2x128_si256(v.add(lo, hi), v.mul(v.sub(lo, hi), tw4), 0x20);
}

// サイズ h ごとに下位 3 段の twiddle ベクトル表を 1 度だけ構築しキャッシュする。
// 順は rate2 (root 系)、逆は irate2 (iroot 系) の prefix product 列から作る。
// twiddle は u32 を 8 個/ブロックで連続格納し、使用時に loadu で読む
// (std::vector<__m256i> は既定アロケータが 32byte 境界を保証せず aligned load が落ちるため)。
template <u32 mod, bool inverse>
struct tail_twiddle {
    int h = -1;
    std::vector<u32> t4, t2, t1;  // 各ブロック 8 要素
    ALGO_AVX2_TARGET void ensure(int h_, const fft_info<mod> &info) {
        if (h_ == h) return;
        using s = mont<mod>;
        h = h_;
        int n = 1 << h, nb = n / 8, half = n / 2;
        std::vector<u32> rot(half > 0 ? half : 1);
        rot[0] = s::to(1);
        for (int st = 0; st + 1 < half; ++st) {
            u32 rate =
                inverse ? info.irate2[std::countr_zero(~(unsigned)st)] : info.rate2[std::countr_zero(~(unsigned)st)];
            rot[st + 1] = s::mul(rot[st], rate);
        }
        t4.resize((size_t)nb * 8);
        t2.resize((size_t)nb * 8);
        t1.resize((size_t)nb * 8);
        for (int b = 0; b < nb; ++b) {
            u32 *p4 = t4.data() + 8 * b, *p2 = t2.data() + 8 * b, *p1 = t1.data() + 8 * b;
            for (int k = 0; k < 8; ++k) p4[k] = rot[b];
            p2[0] = p2[1] = p2[2] = p2[3] = rot[2 * b];
            p2[4] = p2[5] = p2[6] = p2[7] = rot[2 * b + 1];
            p1[0] = p1[1] = rot[4 * b];
            p1[2] = p1[3] = rot[4 * b + 1];
            p1[4] = p1[5] = rot[4 * b + 2];
            p1[6] = p1[7] = rot[4 * b + 3];
        }
    }
    ALGO_AVX2_TARGET inline __m256i v4(int b) const { return _mm256_loadu_si256((__m256i *)(t4.data() + 8 * b)); }
    ALGO_AVX2_TARGET inline __m256i v2(int b) const { return _mm256_loadu_si256((__m256i *)(t2.data() + 8 * b)); }
    ALGO_AVX2_TARGET inline __m256i v1(int b) const { return _mm256_loadu_si256((__m256i *)(t1.data() + 8 * b)); }
};

// 小サイズ (n < 8) 用の純 radix-2 DIF スカラ実装。
template <u32 mod>
ALGO_AVX2_TARGET void butterfly_small(u32 *a, int n, const fft_info<mod> &info) {
    using s = mont<mod>;
    int h = std::countr_zero<unsigned>((unsigned)n);
    for (int len = 0; len < h; ++len) {
        int p = 1 << (h - len - 1);
        u32 rot = s::to(1);
        for (int st = 0; st < (1 << len); ++st) {
            int off = st << (h - len);
            for (int i = 0; i < p; ++i) {
                u32 l = a[i + off], r = s::mul(a[i + off + p], rot);
                a[i + off] = s::add(l, r);
                a[i + off + p] = s::sub(l, r);
            }
            if (st + 1 != (1 << len)) rot = s::mul(rot, info.rate2[std::countr_zero(~(unsigned)st)]);
        }
    }
}

// DIF バタフライ (順変換, 純 radix-2)。上位段 (p>=8) は 8 レーンでベクトル化し、
// 下位 3 段 (p=4,2,1) は 8 要素ブロック内 shuffle (tail_block) で処理する。
template <u32 mod>
ALGO_AVX2_TARGET void butterfly(u32 *a, int n) {
    using s = mont<mod>;
    static const fft_info<mod> info;
    static const montx8<mod> v;
    static tail_twiddle<mod, false> tw;
    int h = std::countr_zero<unsigned>((unsigned)n);
    if (h < 3) {
        butterfly_small<mod>(a, n, info);
        return;
    }
    // 上位段: p = 2^{h-1} .. 8 (len = 0 .. h-4)。
    for (int len = 0; len <= h - 4; ++len) {
        int p = 1 << (h - len - 1);
        u32 rot = s::to(1);
        for (int st = 0; st < (1 << len); ++st) {
            int offset = st << (h - len);
            __m256i vr = _mm256_set1_epi32((int)rot);
            for (int i = 0; i < p; i += 8) {
                __m256i l = _mm256_loadu_si256((__m256i *)(a + i + offset));
                __m256i r = v.mul(_mm256_loadu_si256((__m256i *)(a + i + offset + p)), vr);
                _mm256_storeu_si256((__m256i *)(a + i + offset), v.add(l, r));
                _mm256_storeu_si256((__m256i *)(a + i + offset + p), v.sub(l, r));
            }
            if (st + 1 != (1 << len)) rot = s::mul(rot, info.rate2[std::countr_zero(~(unsigned)st)]);
        }
    }
    // 下位 3 段 (p=4,2,1) を 8 要素ブロックごとに shuffle で。
    tw.ensure(h, info);
    int nb = n / 8;
    for (int b = 0; b < nb; ++b) {
        __m256i x = _mm256_loadu_si256((__m256i *)(a + 8 * b));
        x = tail_block<mod>(x, tw.v4(b), tw.v2(b), tw.v1(b), v);
        _mm256_storeu_si256((__m256i *)(a + 8 * b), x);
    }
}

// 小サイズ (n < 8) 用の純 radix-2 DIT スカラ実装。
template <u32 mod>
ALGO_AVX2_TARGET void butterfly_inv_small(u32 *a, int n, const fft_info<mod> &info) {
    using s = mont<mod>;
    int h = std::countr_zero<unsigned>((unsigned)n);
    for (int len = h; len >= 1; --len) {
        int p = 1 << (h - len);
        u32 irot = s::to(1);
        for (int st = 0; st < (1 << (len - 1)); ++st) {
            int off = st << (h - len + 1);
            for (int i = 0; i < p; ++i) {
                u32 l = a[i + off], r = a[i + off + p];
                a[i + off] = s::add(l, r);
                a[i + off + p] = s::mul(s::sub(l, r), irot);
            }
            if (st + 1 != (1 << (len - 1))) irot = s::mul(irot, info.irate2[std::countr_zero(~(unsigned)st)]);
        }
    }
}

// DIT バタフライ (逆変換, 純 radix-2)。bit-reverse 不要 (順 DIF / 逆 DIT で相殺)。
// 下位 3 段 (p=1,2,4) を先に shuffle (tail_block_inv) で、続いて上位段 (p>=8) をベクトル化。
template <u32 mod>
ALGO_AVX2_TARGET void butterfly_inv(u32 *a, int n) {
    using s = mont<mod>;
    static const fft_info<mod> info;
    static const montx8<mod> v;
    static tail_twiddle<mod, true> tw;
    int h = std::countr_zero<unsigned>((unsigned)n);
    if (h < 3) {
        butterfly_inv_small<mod>(a, n, info);
        return;
    }
    // 下位 3 段 (p=1,2,4) を 8 要素ブロックごとに shuffle で。
    tw.ensure(h, info);
    int nb = n / 8;
    for (int b = 0; b < nb; ++b) {
        __m256i x = _mm256_loadu_si256((__m256i *)(a + 8 * b));
        x = tail_block_inv<mod>(x, tw.v1(b), tw.v2(b), tw.v4(b), v);
        _mm256_storeu_si256((__m256i *)(a + 8 * b), x);
    }
    // 上位段: p = 8 .. 2^{h-1} (len = h-3 .. 1)。
    for (int len = h - 3; len >= 1; --len) {
        int p = 1 << (h - len);
        u32 irot = s::to(1);
        for (int st = 0; st < (1 << (len - 1)); ++st) {
            int offset = st << (h - len + 1);
            __m256i vir = _mm256_set1_epi32((int)irot);
            for (int i = 0; i < p; i += 8) {
                __m256i l = _mm256_loadu_si256((__m256i *)(a + i + offset));
                __m256i r = _mm256_loadu_si256((__m256i *)(a + i + offset + p));
                _mm256_storeu_si256((__m256i *)(a + i + offset), v.add(l, r));
                _mm256_storeu_si256((__m256i *)(a + i + offset + p), v.mul(v.sub(l, r), vir));
            }
            if (st + 1 != (1 << (len - 1))) irot = s::mul(irot, info.irate2[std::countr_zero(~(unsigned)st)]);
        }
    }
}

// [0, mod) の通常表現の係数列 a, b (mod 還元済み) を畳み込む。結果も [0, mod)。
template <u32 mod>
ALGO_AVX2_TARGET std::vector<u32> convolution(const std::vector<u32> &a, const std::vector<u32> &b) {
    using s = mont<mod>;
    int n = (int)a.size(), m = (int)b.size();
    int z = std::bit_ceil<unsigned>(n + m - 1);
    std::vector<u32> fa(z, 0), fb(z, 0);
    for (int i = 0; i < n; ++i) fa[i] = s::to(a[i]);
    for (int i = 0; i < m; ++i) fb[i] = s::to(b[i]);
    butterfly<mod>(fa.data(), z);
    butterfly<mod>(fb.data(), z);
    for (int i = 0; i < z; ++i) fa[i] = s::mul(fa[i], fb[i]);
    butterfly_inv<mod>(fa.data(), z);
    u32 iz = s::inv(s::to((u32)z));
    std::vector<u32> c(n + m - 1);
    for (int i = 0; i < n + m - 1; ++i) c[i] = s::from(s::mul(fa[i], iz));
    return c;
}

// Bostan-Mori の 1 ステップ (DFT 使い回し)。p, q は [0, mod) の通常表現。
// q(-x) (= 奇数次のみ符号反転) の順変換を p*q(-x) と q*q(-x) で共有することで、
// 素朴な 2 畳み込み (6 NTT) を 3 順変換 + 2 逆変換に削減する。
// odd=true なら次の p に奇数次成分を、false なら偶数次成分を採る。
template <u32 mod>
ALGO_AVX2_TARGET void bostan_mori_step(std::vector<u32> &p, std::vector<u32> &q, bool odd) {
    using s = mont<mod>;
    int np = (int)p.size(), nq = (int)q.size();
    int z = std::bit_ceil<unsigned>((unsigned)(2 * nq - 1));

    std::vector<u32> P(z, 0), Q(z, 0), QM(z, 0);
    for (int i = 0; i < np; ++i) P[i] = s::to(p[i]);
    for (int i = 0; i < nq; ++i) {
        u32 v = s::to(q[i]);  // [0, 2*mod)
        Q[i] = v;
        QM[i] = (i & 1) ? (v == 0 ? 0u : 2 * mod - v) : v;  // q(-x) の係数, [0, 2*mod)
    }
    butterfly<mod>(P.data(), z);
    butterfly<mod>(Q.data(), z);
    butterfly<mod>(QM.data(), z);
    for (int i = 0; i < z; ++i) P[i] = s::mul(P[i], QM[i]);  // p(x) q(-x)
    for (int i = 0; i < z; ++i) Q[i] = s::mul(Q[i], QM[i]);  // q(x) q(-x) (偶関数)
    butterfly_inv<mod>(P.data(), z);
    butterfly_inv<mod>(Q.data(), z);
    u32 iz = s::inv(s::to((u32)z));

    // p' は p(x)q(-x) (長さ np+nq-1) の偶/奇成分、q' は q(x)q(-x) (長さ 2nq-1) の偶成分。
    int lp = np + nq - 1, lq = 2 * nq - 1;
    std::vector<u32> rp((lp + (odd ? 0 : 1)) / 2), rq((lq + 1) / 2);
    for (int i = odd ? 1 : 0, k = 0; i < lp; i += 2, ++k) rp[k] = s::from(s::mul(P[i], iz));
    for (int i = 0, k = 0; i < lq; i += 2, ++k) rq[k] = s::from(s::mul(Q[i], iz));
    p = std::move(rp);
    q = std::move(rq);
}

// AVX2 Montgomery NTT による Bostan-Mori。p/q は [0, mod) の通常表現、戻り値も [0, mod)。
// p(x)/q(x) (形式的冪級数) の x^n の係数を返す。n >= 0 を前提とする。
template <u32 mod>
ALGO_AVX2_TARGET u32 bostan_mori(std::vector<u32> p, std::vector<u32> q, std::int64_t n) {
    using s = mont<mod>;
    while (n > 0) {
        if ((int)p.size() >= (int)q.size()) p.resize(q.size() - 1);
        bostan_mori_step<mod>(p, q, n & 1);
        n >>= 1;
    }
    return s::from(s::mul(s::to(p[0]), s::inv(s::to(q[0]))));  // p[0] / q[0]
}

}  // namespace avx2
}  // namespace internal

#undef ALGO_AVX2_TARGET
