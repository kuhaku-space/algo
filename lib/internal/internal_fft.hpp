#pragma once
#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <cstdint>
#include <type_traits>
#include <vector>
#include "internal/internal_math.hpp"
#include "internal/internal_type_traits.hpp"
#include "math/modint.hpp"

namespace internal {

template <internal::static_modint_c mint, int g = internal::primitive_root<mint::mod()>>
struct fft_info {
    static constexpr int rank2 = std::countr_zero<unsigned>(mint::mod() - 1);
    std::array<mint, rank2 + 1> root, iroot;
    std::array<mint, std::max(0, rank2 - 2 + 1)> rate2, irate2;
    std::array<mint, std::max(0, rank2 - 3 + 1)> rate3, irate3;

    fft_info() {
        root[rank2] = mint(g).pow((mint::mod() - 1) >> rank2);
        iroot[rank2] = root[rank2].inv();
        for (int i = rank2 - 1; i >= 0; i--) {
            root[i] = root[i + 1] * root[i + 1];
            iroot[i] = iroot[i + 1] * iroot[i + 1];
        }

        {
            mint prod = 1, iprod = 1;
            for (int i = 0; i <= rank2 - 2; i++) {
                rate2[i] = root[i + 2] * prod;
                irate2[i] = iroot[i + 2] * iprod;
                prod *= iroot[i + 2];
                iprod *= root[i + 2];
            }
        }
        {
            mint prod = 1, iprod = 1;
            for (int i = 0; i <= rank2 - 3; i++) {
                rate3[i] = root[i + 3] * prod;
                irate3[i] = iroot[i + 3] * iprod;
                prod *= iroot[i + 3];
                iprod *= root[i + 3];
            }
        }
    }
};

template <internal::static_modint_c mint>
void butterfly(std::vector<mint> &a) {
    int n = int(a.size());
    int h = std::countr_zero<unsigned>(n);
    static const fft_info<mint> info;
    int len = 0;
    while (len < h) {
        if (h - len == 1) {
            int p = 1 << (h - len - 1);
            mint rot = 1;
            for (int s = 0; s < (1 << len); s++) {
                int offset = s << (h - len);
                for (int i = 0; i < p; i++) {
                    auto l = a[i + offset], r = a[i + offset + p] * rot;
                    a[i + offset] = l + r, a[i + offset + p] = l - r;
                }
                if (s + 1 != (1 << len)) rot *= info.rate2[std::countr_zero(~(unsigned int)(s))];
            }
            len++;
        } else {
            int p = 1 << (h - len - 2);
            mint rot = 1, imag = info.root[2];
            for (int s = 0; s < (1 << len); s++) {
                mint rot2 = rot * rot;
                mint rot3 = rot2 * rot;
                int offset = s << (h - len);
                for (int i = 0; i < p; i++) {
                    auto mod2 = 1ull * mint::mod() * mint::mod();
                    auto a0 = 1ull * a[i + offset].val();
                    auto a1 = 1ull * a[i + offset + p].val() * rot.val();
                    auto a2 = 1ull * a[i + offset + 2 * p].val() * rot2.val();
                    auto a3 = 1ull * a[i + offset + 3 * p].val() * rot3.val();
                    auto a1na3imag = 1ull * mint(a1 + mod2 - a3).val() * imag.val();
                    auto na2 = mod2 - a2;
                    a[i + offset] = a0 + a2 + a1 + a3;
                    a[i + offset + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));
                    a[i + offset + 2 * p] = a0 + na2 + a1na3imag;
                    a[i + offset + 3 * p] = a0 + na2 + (mod2 - a1na3imag);
                }
                if (s + 1 != (1 << len)) rot *= info.rate3[std::countr_zero(~(unsigned int)(s))];
            }
            len += 2;
        }
    }
}

template <internal::static_modint_c mint>
void butterfly_inv(std::vector<mint> &a) {
    int n = int(a.size());
    int h = std::countr_zero<unsigned>(n);
    static const fft_info<mint> info;
    int len = h;
    while (len) {
        if (len == 1) {
            int p = 1 << (h - len);
            mint irot = 1;
            for (int s = 0; s < (1 << (len - 1)); s++) {
                int offset = s << (h - len + 1);
                for (int i = 0; i < p; i++) {
                    auto l = a[i + offset], r = a[i + offset + p];
                    a[i + offset] = l + r;
                    a[i + offset + p] = (std::uint64_t)(mint::mod() + l.val() - r.val()) * irot.val();
                }
                if (s + 1 != (1 << (len - 1))) irot *= info.irate2[std::countr_zero(~(unsigned int)(s))];
            }
            len--;
        } else {
            int p = 1 << (h - len);
            mint irot = 1, iimag = info.iroot[2];
            for (int s = 0; s < (1 << (len - 2)); s++) {
                mint irot2 = irot * irot;
                mint irot3 = irot2 * irot;
                int offset = s << (h - len + 2);
                for (int i = 0; i < p; i++) {
                    auto a0 = 1ull * a[i + offset + 0 * p].val();
                    auto a1 = 1ull * a[i + offset + 1 * p].val();
                    auto a2 = 1ull * a[i + offset + 2 * p].val();
                    auto a3 = 1ull * a[i + offset + 3 * p].val();
                    auto a2na3iimag = 1ull * mint((mint::mod() + a2 - a3) * iimag.val()).val();
                    a[i + offset] = a0 + a1 + a2 + a3;
                    a[i + offset + 1 * p] = (a0 + (mint::mod() - a1) + a2na3iimag) * irot.val();
                    a[i + offset + 2 * p] = (a0 + a1 + (mint::mod() - a2) + (mint::mod() - a3)) * irot2.val();
                    a[i + offset + 3 * p] = (a0 + (mint::mod() - a1) + (mint::mod() - a2na3iimag)) * irot3.val();
                }
                if (s + 1 != (1 << (len - 2))) irot *= info.irate3[std::countr_zero(~(unsigned int)(s))];
            }
            len -= 2;
        }
    }
}

template <internal::static_modint_c mint>
std::vector<mint> convolution_naive(const std::vector<mint> &a, const std::vector<mint> &b) {
    int n = int(a.size()), m = int(b.size());
    std::vector<mint> ans(n + m - 1);
    if (n < m) {
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) ans[i + j] += a[i] * b[j];
        }
    } else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) ans[i + j] += a[i] * b[j];
        }
    }
    return ans;
}

template <internal::static_modint_c mint>
std::vector<mint> convolution_fft(std::vector<mint> a, std::vector<mint> b) {
    int n = int(a.size()), m = int(b.size());
    int z = std::bit_ceil<unsigned>(n + m - 1);
    a.resize(z);
    internal::butterfly(a);
    b.resize(z);
    internal::butterfly(b);
    for (int i = 0; i < z; i++) { a[i] *= b[i]; }
    internal::butterfly_inv(a);
    a.resize(n + m - 1);
    mint iz = mint(z).inv();
    for (int i = 0; i < n + m - 1; i++) a[i] *= iz;
    return a;
}

/// 自乗畳み込み (a と a の畳み込み)。順変換が 1 回で済むため通常の 3 NTT に対し 2 NTT で計算できる。
/// @see https://noshi91.hatenablog.com/entry/2023/12/10/163348 (DFT の使いまわし)
template <internal::static_modint_c mint>
std::vector<mint> convolution_fft_square(std::vector<mint> a) {
    int n = int(a.size());
    int z = std::bit_ceil<unsigned>(2 * n - 1);
    a.resize(z);
    internal::butterfly(a);
    for (int i = 0; i < z; i++) { a[i] *= a[i]; }
    internal::butterfly_inv(a);
    a.resize(2 * n - 1);
    mint iz = mint(z).inv();
    for (int i = 0; i < 2 * n - 1; i++) a[i] *= iz;
    return a;
}

/// middle product (転置乗算): a (長さ n) と b (長さ m, n >= m) に対し
/// c[i] = sum_{j=0}^{m-1} a[i+j] * b[j]  (i = 0 .. n-m) を返す (長さ n-m+1)。
/// これは a と rev(b) のフル積 a*rev(b) の添字 m-1 .. n-1 にあたる。
/// サイズ bit_ceil(n) の巡回畳み込み 1 回で求まる。z >= n より該当範囲には巻き込みが起きない。
/// @see https://noshi91.hatenablog.com/entry/2023/12/10/163348 (Middle Product)
template <internal::static_modint_c mint>
std::vector<mint> middle_product_fft(std::vector<mint> a, std::vector<mint> b) {
    int n = int(a.size()), m = int(b.size());
    std::reverse(b.begin(), b.end());
    int z = std::bit_ceil<unsigned>(n);
    a.resize(z);
    b.resize(z);
    internal::butterfly(a);
    internal::butterfly(b);
    for (int i = 0; i < z; i++) { a[i] *= b[i]; }
    internal::butterfly_inv(a);
    mint iz = mint(z).inv();
    std::vector<mint> c(n - m + 1);
    for (int i = 0; i < n - m + 1; i++) c[i] = a[i + m - 1] * iz;
    return c;
}

template <internal::static_modint_c mint>
std::vector<mint> middle_product_naive(const std::vector<mint> &a, const std::vector<mint> &b) {
    int n = int(a.size()), m = int(b.size());
    std::vector<mint> c(n - m + 1);
    for (int i = 0; i < n - m + 1; i++) {
        for (int j = 0; j < m; j++) c[i] += a[i + j] * b[j];
    }
    return c;
}

/// 任意 mod / 任意係数の畳み込みで使う 3 つの NTT-friendly 素数と Garner 法用の定数。
/// MOD1 < MOD2 < MOD3 で、いずれも 2^24 まで NTT 可能 (最小は MOD1 の 2^24)。
struct convolution_mod_constants {
    static constexpr std::uint64_t MOD1 = 754974721;  // 45 * 2^24 + 1, NTT 可能長 2^24
    static constexpr std::uint64_t MOD2 = 167772161;  // 5  * 2^25 + 1, NTT 可能長 2^25
    static constexpr std::uint64_t MOD3 = 469762049;  // 7  * 2^26 + 1, NTT 可能長 2^26
    static constexpr std::uint64_t M2M3 = MOD2 * MOD3;
    static constexpr std::uint64_t M1M3 = MOD1 * MOD3;
    static constexpr std::uint64_t M1M2 = MOD1 * MOD2;
    // MOD_jM_l を法とした MOD_kの逆元 (Garner 復元用)。inv_gcd は非負を返す。
    static constexpr std::uint64_t i1 = internal::inv_gcd(MOD2 * MOD3, MOD1).second;
    static constexpr std::uint64_t i2 = internal::inv_gcd(MOD1 * MOD3, MOD2).second;
    static constexpr std::uint64_t i3 = internal::inv_gcd(MOD1 * MOD2, MOD3).second;
    // 畳み込み可能な最大長は min(各素数の NTT 可能長) = MOD1 の 2^24。
    static constexpr int MAX_AB_BIT = 24;
    static_assert(MOD1 % (1ull << MAX_AB_BIT) == 1, "MOD1 isn't enough to support an array length of 2^24.");
    static_assert(MOD2 % (1ull << MAX_AB_BIT) == 1, "MOD2 isn't enough to support an array length of 2^24.");
    static_assert(MOD3 % (1ull << MAX_AB_BIT) == 1, "MOD3 isn't enough to support an array length of 2^24.");
};

}  // namespace internal
