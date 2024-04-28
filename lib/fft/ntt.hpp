#include <algorithm>
#include <cassert>
#include <type_traits>
#include <vector>
#include "internal/internal_fft.hpp"
#include "template/template.hpp"

/**
 * @brief 畳み込み
 *
 * @tparam mint
 * @param a
 * @param b
 * @return std::vector<mint>
 */
template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> convolution(std::vector<mint> &&a, std::vector<mint> &&b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};

    int z = (int)internal::bit_ceil((unsigned int)(n + m - 1));
    assert((mint::mod() - 1) % z == 0);

    if (std::min(n, m) <= 60) return convolution_naive(a, b);
    return internal::convolution_fft(a, b);
}
template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> convolution(const std::vector<mint> &a, const std::vector<mint> &b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};

    int z = (int)internal::bit_ceil((unsigned int)(n + m - 1));
    assert((mint::mod() - 1) % z == 0);

    if (std::min(n, m) <= 60) return convolution_naive(a, b);
    return internal::convolution_fft(a, b);
}

template <unsigned int mod = 998244353, class T,
          std::enable_if_t<std::is_integral<T>::value> * = nullptr>
std::vector<T> convolution(const std::vector<T> &a, const std::vector<T> &b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};

    using mint = static_modint<mod>;

    int z = (int)internal::bit_ceil((unsigned int)(n + m - 1));
    assert((mint::mod() - 1) % z == 0);

    std::vector<mint> a2(n), b2(m);
    for (int i = 0; i < n; i++) { a2[i] = mint(a[i]); }
    for (int i = 0; i < m; i++) { b2[i] = mint(b[i]); }
    auto c2 = convolution(std::move(a2), std::move(b2));
    std::vector<T> c(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) { c[i] = c2[i].val(); }
    return c;
}

std::vector<std::int64_t> convolution_ll(const std::vector<std::int64_t> &a,
                                         const std::vector<std::int64_t> &b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};

    static constexpr std::uint64_t MOD1 = 754974721;  // 2^24
    static constexpr std::uint64_t MOD2 = 167772161;  // 2^25
    static constexpr std::uint64_t MOD3 = 469762049;  // 2^26
    static constexpr std::uint64_t M2M3 = MOD2 * MOD3;
    static constexpr std::uint64_t M1M3 = MOD1 * MOD3;
    static constexpr std::uint64_t M1M2 = MOD1 * MOD2;
    static constexpr std::uint64_t M1M2M3 = MOD1 * MOD2 * MOD3;

    static constexpr std::uint64_t i1 = internal::inv_gcd(MOD2 * MOD3, MOD1).second;
    static constexpr std::uint64_t i2 = internal::inv_gcd(MOD1 * MOD3, MOD2).second;
    static constexpr std::uint64_t i3 = internal::inv_gcd(MOD1 * MOD2, MOD3).second;

    static constexpr int MAX_AB_BIT = 24;
    static_assert(MOD1 % (1ull << MAX_AB_BIT) == 1,
                  "MOD1 isn't enough to support an array length of 2^24.");
    static_assert(MOD2 % (1ull << MAX_AB_BIT) == 1,
                  "MOD2 isn't enough to support an array length of 2^24.");
    static_assert(MOD3 % (1ull << MAX_AB_BIT) == 1,
                  "MOD3 isn't enough to support an array length of 2^24.");
    assert(n + m - 1 <= (1 << MAX_AB_BIT));

    auto c1 = convolution<MOD1>(a, b);
    auto c2 = convolution<MOD2>(a, b);
    auto c3 = convolution<MOD3>(a, b);

    std::vector<std::int64_t> c(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) {
        std::uint64_t x = 0;
        x += (c1[i] * i1) % MOD1 * M2M3;
        x += (c2[i] * i2) % MOD2 * M1M3;
        x += (c3[i] * i3) % MOD3 * M1M2;
        std::int64_t diff = c1[i] - internal::safe_mod((std::int64_t)(x), (std::int64_t)(MOD1));
        if (diff < 0) diff += MOD1;
        static constexpr std::uint64_t offset[5] = {0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3};
        x -= offset[diff % 5];
        c[i] = x;
    }

    return c;
}
