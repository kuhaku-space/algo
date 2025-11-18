#pragma once
#include "fft/ntt.hpp"
#include "template/template.hpp"

/**
 * @brief 任意mod畳み込み
 *
 * @tparam mod
 * @tparam T
 * @param a
 * @param b
 * @return std::vector<T>
 *
 * @see https://math314.hateblo.jp/entry/2015/05/07/014908
 * @see https://asako.growi.cloud/compro/NTT
 */
template <unsigned int mod = 998244353, class T, std::enable_if_t<std::is_integral<T>::value> * = nullptr>
std::vector<T> convolution_mod(const std::vector<T> &a, const std::vector<T> &b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};

    static constexpr std::uint64_t MOD1 = 754974721;  // 2^24
    static constexpr std::uint64_t MOD2 = 167772161;  // 2^25
    static constexpr std::uint64_t MOD3 = 469762049;  // 2^26
    static constexpr std::uint64_t M2M3 = MOD2 * MOD3;
    static constexpr std::uint64_t M1M3 = MOD1 * MOD3;
    static constexpr std::uint64_t M1M2 = MOD1 * MOD2;
    static constexpr __uint128_t M1M2M3 = (__uint128_t)MOD1 * MOD2 * MOD3;

    static constexpr std::uint64_t i1 = internal::inv_gcd(MOD2 * MOD3, MOD1).second;
    static constexpr std::uint64_t i2 = internal::inv_gcd(MOD1 * MOD3, MOD2).second;
    static constexpr std::uint64_t i3 = internal::inv_gcd(MOD1 * MOD2, MOD3).second;

    static constexpr int MAX_AB_BIT = 24;
    static_assert(MOD1 % (1ull << MAX_AB_BIT) == 1, "MOD1 isn't enough to support an array length of 2^24.");
    static_assert(MOD2 % (1ull << MAX_AB_BIT) == 1, "MOD2 isn't enough to support an array length of 2^24.");
    static_assert(MOD3 % (1ull << MAX_AB_BIT) == 1, "MOD3 isn't enough to support an array length of 2^24.");
    assert(n + m - 1 <= (1 << MAX_AB_BIT));

    auto c1 = convolution<MOD1>(a, b);
    auto c2 = convolution<MOD2>(a, b);
    auto c3 = convolution<MOD3>(a, b);

    std::vector<T> c(n + m - 1);
    for (int i = 0; i < n + m - 1; ++i) {
        __uint128_t x = (c1[i] * i1) % MOD1 * (__uint128_t)M2M3;
        x += (c2[i] * i2) % MOD2 * (__uint128_t)M1M3;
        if (x >= M1M2M3) x -= M1M2M3;
        x += (c3[i] * i3) % MOD3 * (__uint128_t)M1M2;
        if (x >= M1M2M3) x -= M1M2M3;
        c[i] = x % mod;
    }

    return c;
}
