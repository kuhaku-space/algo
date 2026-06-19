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

template <u32 mod, int g = internal::primitive_root<(int)mod>>
struct fft_info {
    using s = mont<mod>;
    static constexpr int rank2 = std::countr_zero<unsigned>(mod - 1);
    std::array<u32, rank2 + 1> root, iroot;  // Montgomery 表現
    std::array<u32, std::max(0, rank2 - 1)> rate2, irate2;
    std::array<u32, std::max(0, rank2 - 2)> rate3, irate3;
    fft_info() {
        root[rank2] = s::pow(s::to(g), (mod - 1) >> rank2);
        iroot[rank2] = s::inv(root[rank2]);
        for (int i = rank2 - 1; i >= 0; --i) {
            root[i] = s::mul(root[i + 1], root[i + 1]);
            iroot[i] = s::mul(iroot[i + 1], iroot[i + 1]);
        }
        {
            u32 prod = s::to(1), iprod = s::to(1);
            for (int i = 0; i <= rank2 - 2; ++i) {
                rate2[i] = s::mul(root[i + 2], prod);
                irate2[i] = s::mul(iroot[i + 2], iprod);
                prod = s::mul(prod, iroot[i + 2]);
                iprod = s::mul(iprod, root[i + 2]);
            }
        }
        {
            u32 prod = s::to(1), iprod = s::to(1);
            for (int i = 0; i <= rank2 - 3; ++i) {
                rate3[i] = s::mul(root[i + 3], prod);
                irate3[i] = s::mul(iroot[i + 3], iprod);
                prod = s::mul(prod, iroot[i + 3]);
                iprod = s::mul(iprod, root[i + 3]);
            }
        }
    }
};

// DIF バタフライ (順変換)。a は長さ n = 2^h の Montgomery 表現配列。
template <u32 mod>
ALGO_AVX2_TARGET void butterfly(u32 *a, int n) {
    using s = mont<mod>;
    static const fft_info<mod> info;
    static const montx8<mod> v;
    int h = std::countr_zero<unsigned>((unsigned)n);
    int len = 0;
    while (len < h) {
        if (h - len == 1) {
            int p = 1 << (h - len - 1);
            u32 rot = s::to(1);
            for (int st = 0; st < (1 << len); ++st) {
                int offset = st << (h - len);
                if (p >= 8) {
                    __m256i vr = _mm256_set1_epi32((int)rot);
                    for (int i = 0; i < p; i += 8) {
                        __m256i l = _mm256_loadu_si256((__m256i *)(a + i + offset));
                        __m256i r = v.mul(_mm256_loadu_si256((__m256i *)(a + i + offset + p)), vr);
                        _mm256_storeu_si256((__m256i *)(a + i + offset), v.add(l, r));
                        _mm256_storeu_si256((__m256i *)(a + i + offset + p), v.sub(l, r));
                    }
                } else {
                    for (int i = 0; i < p; ++i) {
                        u32 l = a[i + offset], r = s::mul(a[i + offset + p], rot);
                        a[i + offset] = s::add(l, r);
                        a[i + offset + p] = s::sub(l, r);
                    }
                }
                if (st + 1 != (1 << len)) rot = s::mul(rot, info.rate2[std::countr_zero(~(unsigned)st)]);
            }
            ++len;
        } else {
            int p = 1 << (h - len - 2);
            u32 rot = s::to(1), imag = info.root[2];
            for (int st = 0; st < (1 << len); ++st) {
                u32 rot2 = s::mul(rot, rot), rot3 = s::mul(rot2, rot);
                int offset = st << (h - len);
                if (p >= 8) {
                    __m256i vr = _mm256_set1_epi32((int)rot), vr2 = _mm256_set1_epi32((int)rot2),
                            vr3 = _mm256_set1_epi32((int)rot3), vim = _mm256_set1_epi32((int)imag);
                    for (int i = 0; i < p; i += 8) {
                        __m256i a0 = _mm256_loadu_si256((__m256i *)(a + i + offset));
                        __m256i a1 = v.mul(_mm256_loadu_si256((__m256i *)(a + i + offset + p)), vr);
                        __m256i a2 = v.mul(_mm256_loadu_si256((__m256i *)(a + i + offset + 2 * p)), vr2);
                        __m256i a3 = v.mul(_mm256_loadu_si256((__m256i *)(a + i + offset + 3 * p)), vr3);
                        __m256i a1na3im = v.mul(v.sub(a1, a3), vim);
                        __m256i a0a2 = v.add(a0, a2), a0na2 = v.sub(a0, a2), a1a3 = v.add(a1, a3);
                        _mm256_storeu_si256((__m256i *)(a + i + offset), v.add(a0a2, a1a3));
                        _mm256_storeu_si256((__m256i *)(a + i + offset + p), v.sub(a0a2, a1a3));
                        _mm256_storeu_si256((__m256i *)(a + i + offset + 2 * p), v.add(a0na2, a1na3im));
                        _mm256_storeu_si256((__m256i *)(a + i + offset + 3 * p), v.sub(a0na2, a1na3im));
                    }
                } else {
                    for (int i = 0; i < p; ++i) {
                        u32 a0 = a[i + offset], a1 = s::mul(a[i + offset + p], rot),
                            a2 = s::mul(a[i + offset + 2 * p], rot2), a3 = s::mul(a[i + offset + 3 * p], rot3);
                        u32 a1na3im = s::mul(s::sub(a1, a3), imag);
                        u32 a0a2 = s::add(a0, a2), a0na2 = s::sub(a0, a2), a1a3 = s::add(a1, a3);
                        a[i + offset] = s::add(a0a2, a1a3);
                        a[i + offset + p] = s::sub(a0a2, a1a3);
                        a[i + offset + 2 * p] = s::add(a0na2, a1na3im);
                        a[i + offset + 3 * p] = s::sub(a0na2, a1na3im);
                    }
                }
                if (st + 1 != (1 << len)) rot = s::mul(rot, info.rate3[std::countr_zero(~(unsigned)st)]);
            }
            len += 2;
        }
    }
}

// DIT バタフライ (逆変換)。bit-reverse 不要 (順 DIF / 逆 DIT で相殺)。
template <u32 mod>
ALGO_AVX2_TARGET void butterfly_inv(u32 *a, int n) {
    using s = mont<mod>;
    static const fft_info<mod> info;
    static const montx8<mod> v;
    int h = std::countr_zero<unsigned>((unsigned)n);
    int len = h;
    while (len) {
        if (len == 1) {
            int p = 1 << (h - len);
            u32 irot = s::to(1);
            for (int st = 0; st < (1 << (len - 1)); ++st) {
                int offset = st << (h - len + 1);
                if (p >= 8) {
                    __m256i vir = _mm256_set1_epi32((int)irot);
                    for (int i = 0; i < p; i += 8) {
                        __m256i l = _mm256_loadu_si256((__m256i *)(a + i + offset));
                        __m256i r = _mm256_loadu_si256((__m256i *)(a + i + offset + p));
                        _mm256_storeu_si256((__m256i *)(a + i + offset), v.add(l, r));
                        _mm256_storeu_si256((__m256i *)(a + i + offset + p), v.mul(v.sub(l, r), vir));
                    }
                } else {
                    for (int i = 0; i < p; ++i) {
                        u32 l = a[i + offset], r = a[i + offset + p];
                        a[i + offset] = s::add(l, r);
                        a[i + offset + p] = s::mul(s::sub(l, r), irot);
                    }
                }
                if (st + 1 != (1 << (len - 1))) irot = s::mul(irot, info.irate2[std::countr_zero(~(unsigned)st)]);
            }
            --len;
        } else {
            int p = 1 << (h - len);
            u32 irot = s::to(1), iimag = info.iroot[2];
            for (int st = 0; st < (1 << (len - 2)); ++st) {
                u32 irot2 = s::mul(irot, irot), irot3 = s::mul(irot2, irot);
                int offset = st << (h - len + 2);
                if (p >= 8) {
                    __m256i vir = _mm256_set1_epi32((int)irot), vir2 = _mm256_set1_epi32((int)irot2),
                            vir3 = _mm256_set1_epi32((int)irot3), vim = _mm256_set1_epi32((int)iimag);
                    for (int i = 0; i < p; i += 8) {
                        __m256i a0 = _mm256_loadu_si256((__m256i *)(a + i + offset));
                        __m256i a1 = _mm256_loadu_si256((__m256i *)(a + i + offset + p));
                        __m256i a2 = _mm256_loadu_si256((__m256i *)(a + i + offset + 2 * p));
                        __m256i a3 = _mm256_loadu_si256((__m256i *)(a + i + offset + 3 * p));
                        __m256i a2na3im = v.mul(v.sub(a2, a3), vim);
                        __m256i a0a1 = v.add(a0, a1), a0na1 = v.sub(a0, a1), a2a3 = v.add(a2, a3);
                        _mm256_storeu_si256((__m256i *)(a + i + offset), v.add(a0a1, a2a3));
                        _mm256_storeu_si256((__m256i *)(a + i + offset + p), v.mul(v.add(a0na1, a2na3im), vir));
                        _mm256_storeu_si256((__m256i *)(a + i + offset + 2 * p), v.mul(v.sub(a0a1, a2a3), vir2));
                        _mm256_storeu_si256((__m256i *)(a + i + offset + 3 * p), v.mul(v.sub(a0na1, a2na3im), vir3));
                    }
                } else {
                    for (int i = 0; i < p; ++i) {
                        u32 a0 = a[i + offset], a1 = a[i + offset + p], a2 = a[i + offset + 2 * p],
                            a3 = a[i + offset + 3 * p];
                        u32 a2na3im = s::mul(s::sub(a2, a3), iimag);
                        u32 a0a1 = s::add(a0, a1), a0na1 = s::sub(a0, a1), a2a3 = s::add(a2, a3);
                        a[i + offset] = s::add(a0a1, a2a3);
                        a[i + offset + p] = s::mul(s::add(a0na1, a2na3im), irot);
                        a[i + offset + 2 * p] = s::mul(s::sub(a0a1, a2a3), irot2);
                        a[i + offset + 3 * p] = s::mul(s::sub(a0na1, a2na3im), irot3);
                    }
                }
                if (st + 1 != (1 << (len - 2))) irot = s::mul(irot, info.irate3[std::countr_zero(~(unsigned)st)]);
            }
            len -= 2;
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

}  // namespace avx2
}  // namespace internal

#undef ALGO_AVX2_TARGET
