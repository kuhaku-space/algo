#pragma once
#include <bit>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <vector>
#include "fft/ntt.hpp"
#include "internal/internal_fft_avx2.hpp"

namespace internal {
// 実行時に AVX2 が使えるか。x86 (GCC/Clang) では CPU 機能を実行時判定し、
// それ以外のアーキテクチャでは常に false (通常の NTT にフォールバック)。
inline bool has_avx2() {
#if defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
    return __builtin_cpu_supports("avx2");
#else
    return false;
#endif
}
}  // namespace internal

/// @brief Montgomery + AVX2 による NTT 畳み込み (NTT-friendly な 32bit 素数 mod 専用)
/// @details 値を [0, 2*mod) の Montgomery 表現で 8 レーン (u32x8) 同時に処理する。
///          通常の convolution より定数倍が小さい (mod=998244353, N=2^20 で約 1.5 倍速)。
///          AVX2 が使えない CPU では実行時に通常の convolution へフォールバックする。
/// @note mod は 2 < mod < 2^30 の NTT-friendly 素数であること (Montgomery 簡約・遅延簡約の
///       桁あふれ回避のため 2^30 未満を要求)。
/// @see https://tayu0110.hatenablog.com/entry/2023/05/06/023244
/// @tparam mod NTT-friendly な素数 mod (既定: 998244353)
/// @tparam T 整数型 (std::integral)
/// @param a 入力多項式の係数列
/// @param b 入力多項式の係数列
/// @return std::vector<T> a と b の畳み込みを mod で取った値 (長さ a.size() + b.size() - 1)
template <unsigned int mod = 998244353, std::integral T>
std::vector<T> convolution_avx2(const std::vector<T> &a, const std::vector<T> &b) {
    static_assert(internal::is_prime<(int)mod>, "mod must be prime");
    static_assert(mod < (1u << 30), "mod must be < 2^30 for the AVX2 Montgomery NTT");

    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};
    assert((mod - 1) % std::bit_ceil<unsigned>(n + m - 1) == 0);

    if (!internal::has_avx2()) return convolution<mod>(a, b);

    std::vector<std::uint32_t> ua(n), ub(m);
    for (int i = 0; i < n; ++i) {
        std::int64_t x = (std::int64_t)a[i] % (std::int64_t)mod;
        ua[i] = (std::uint32_t)(x < 0 ? x + mod : x);
    }
    for (int i = 0; i < m; ++i) {
        std::int64_t x = (std::int64_t)b[i] % (std::int64_t)mod;
        ub[i] = (std::uint32_t)(x < 0 ? x + mod : x);
    }
    auto uc = internal::avx2::convolution<mod>(ua, ub);
    std::vector<T> c(n + m - 1);
    for (int i = 0; i < n + m - 1; ++i) c[i] = (T)uc[i];
    return c;
}

/// @brief Montgomery + AVX2 による NTT 畳み込み (static_modint 版)
/// @tparam mint NTT-friendly な static modint (mod < 2^30)
/// @param a 入力多項式の係数列
/// @param b 入力多項式の係数列
/// @return std::vector<mint> a と b の畳み込み (長さ a.size() + b.size() - 1)
template <internal::static_modint_c mint>
std::vector<mint> convolution_avx2(const std::vector<mint> &a, const std::vector<mint> &b) {
    constexpr unsigned int mod = (unsigned int)mint::mod();
    static_assert(mod < (1u << 30), "mod must be < 2^30 for the AVX2 Montgomery NTT");

    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};
    assert((mod - 1) % std::bit_ceil<unsigned>(n + m - 1) == 0);

    if (!internal::has_avx2()) return convolution(a, b);

    std::vector<std::uint32_t> ua(n), ub(m);
    for (int i = 0; i < n; ++i) ua[i] = a[i].val();
    for (int i = 0; i < m; ++i) ub[i] = b[i].val();
    auto uc = internal::avx2::convolution<mod>(ua, ub);
    std::vector<mint> c(n + m - 1);
    for (int i = 0; i < n + m - 1; ++i) c[i] = mint::raw((int)uc[i]);
    return c;
}
