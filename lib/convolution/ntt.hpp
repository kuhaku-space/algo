#pragma once
#include <algorithm>
#include <bit>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <vector>
#include "internal/internal_fft.hpp"

/// @brief 愚直畳み込みへ切り替える入力サイズの閾値
/// @complexity コンパイル時定数で実行時計算量はない
static constexpr int CONVOLUTION_NAIVE_THRESHOLD = 60;

/// @brief NTT による畳み込み (modint 版)
/// @tparam mint NTT-friendly な static modint (mod - 1 が畳み込み長で割り切れること)
/// @param a 入力多項式の係数列
/// @param b 入力多項式の係数列
/// @return std::vector<mint> a と b の畳み込み (長さ a.size() + b.size() - 1)
/// @complexity 出力長を $N$ として $O(N\log N)$
template <internal::static_modint_c mint>
std::vector<mint> convolution(const std::vector<mint> &a, const std::vector<mint> &b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};

    assert((mint::mod() - 1) % std::bit_ceil<unsigned>(n + m - 1) == 0);

    if (std::min(n, m) <= CONVOLUTION_NAIVE_THRESHOLD) return internal::convolution_naive(a, b);
    // 同一列同士の畳み込みは順変換が 1 回で済む (3 NTT -> 2 NTT)。比較は O(n) で NTT より十分軽い。
    if (n == m && a == b) return internal::convolution_fft_square(a);
    return internal::convolution_fft(a, b);
}

/// @brief 自乗畳み込み (a と a の畳み込み, modint 版)
/// @details a を自身と畳み込む。順変換を 1 回に削減できるため convolution(a, a) より速い。
/// @tparam mint NTT-friendly な static modint
/// @param a 入力多項式の係数列
/// @return std::vector<mint> a と a の畳み込み (長さ 2 * a.size() - 1)
/// @see https://noshi91.hatenablog.com/entry/2023/12/10/163348
/// @complexity 出力長を $N$ として $O(N\log N)$
template <internal::static_modint_c mint>
std::vector<mint> convolution_square(const std::vector<mint> &a) {
    int n = int(a.size());
    if (!n) return {};

    assert((mint::mod() - 1) % std::bit_ceil<unsigned>(2 * n - 1) == 0);

    if (n <= CONVOLUTION_NAIVE_THRESHOLD) return internal::convolution_naive(a, a);
    return internal::convolution_fft_square(a);
}

/// @brief NTT による畳み込み (整数版)
/// @note 各係数は modint コンストラクタを通して mod で正規化される (負値も可)。
/// @tparam mod NTT-friendly な素数 mod (既定: 998244353)
/// @tparam T 整数型 (std::integral)
/// @param a 入力多項式の係数列
/// @param b 入力多項式の係数列
/// @return std::vector<T> a と b の畳み込みを mod で取った値 (長さ a.size() + b.size() - 1)
/// @complexity 出力長を $N$ として $O(N\log N)$
template <unsigned int mod = 998244353, std::integral T>
std::vector<T> convolution(const std::vector<T> &a, const std::vector<T> &b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};

    using mint = static_modint<mod>;

    assert((mint::mod() - 1) % std::bit_ceil<unsigned>(n + m - 1) == 0);

    std::vector<mint> a2(n), b2(m);
    for (int i = 0; i < n; i++) { a2[i] = mint(a[i]); }
    for (int i = 0; i < m; i++) { b2[i] = mint(b[i]); }
    auto c2 = convolution(a2, b2);
    std::vector<T> c(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) { c[i] = c2[i].val(); }
    return c;
}

/// @brief middle product / 転置乗算 (modint 版)
/// @details a (長さ n) と b (長さ m, m <= n) に対し c[i] = sum_j a[i+j] * b[j]
///          (i = 0 .. n-m) を返す (長さ n-m+1)。a と rev(b) のフル積の中央部に等しく、
///          変換長が bit_ceil(n) で済む。多項式補間・分割統治など「ずらし内積」が要る場面で使う。
/// @tparam mint NTT-friendly な static modint
/// @param a 長さ n の係数列
/// @param b 長さ m (m <= n) の係数列
/// @return std::vector<mint> c[i] = sum_j a[i+j]*b[j] (長さ n - m + 1)
/// @see https://noshi91.hatenablog.com/entry/2023/12/10/163348
/// @complexity $n=|a|$ として $O(n\log n)$
template <internal::static_modint_c mint>
std::vector<mint> middle_product(const std::vector<mint> &a, const std::vector<mint> &b) {
    int n = int(a.size()), m = int(b.size());
    assert(m <= n);
    if (!m) return {};

    assert((mint::mod() - 1) % std::bit_ceil<unsigned>(n) == 0);

    if (std::min(n, m) <= CONVOLUTION_NAIVE_THRESHOLD) return internal::middle_product_naive(a, b);
    return internal::middle_product_fft(a, b);
}

/// @brief 任意係数の畳み込み (3 つの NTT + Garner 法)
/// @details 3 つの NTT-friendly 素数で畳み込み、Garner 法で復元することで
///          オーバーフローしない範囲の int64_t 畳み込みを求める。
/// @note 畳み込み後の長さは 2^24 (約 1.6e7) 以下でなければならない。
/// @param a 入力多項式の係数列
/// @param b 入力多項式の係数列
/// @return std::vector<std::int64_t> a と b の畳み込み (長さ a.size() + b.size() - 1)
/// @complexity 出力長を $N$ として $O(N\log N)$
std::vector<std::int64_t> convolution_ll(const std::vector<std::int64_t> &a, const std::vector<std::int64_t> &b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};

    using C = internal::convolution_mod_constants;
    static constexpr std::uint64_t M1M2M3 = C::MOD1 * C::MOD2 * C::MOD3;
    assert(n + m - 1 <= (1 << C::MAX_AB_BIT));

    auto c1 = convolution<C::MOD1>(a, b);
    auto c2 = convolution<C::MOD2>(a, b);
    auto c3 = convolution<C::MOD3>(a, b);

    std::vector<std::int64_t> c(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) {
        // Garner 法で得た値を mod 2^64 で計算する (各項・総和は 2^64 を超えて
        // 自然にラップする。真値との差は M1M2M3 の倍数なので後で補正できる)。
        std::uint64_t x = 0;
        x += (c1[i] * C::i1) % C::MOD1 * C::M2M3;
        x += (c2[i] * C::i2) % C::MOD2 * C::M1M3;
        x += (c3[i] * C::i3) % C::MOD3 * C::M1M2;
        // x mod MOD1 と真値 c1[i] のズレから、引くべき M1M2M3 の倍数 (0..3) を求めて補正する。
        std::int64_t diff = c1[i] - internal::safe_mod((std::int64_t)(x), (std::int64_t)(C::MOD1));
        if (diff < 0) diff += C::MOD1;
        static constexpr std::uint64_t offset[5] = {0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3};
        x -= offset[diff % 5];
        c[i] = (std::int64_t)x;
    }

    return c;
}

/// @brief 係数積が小さいときの畳み込み (2 つの NTT + CRT)
/// @details MOD1 (= 754974721) と MOD3 (= 469762049) の 2 素数だけで畳み込み、
///          CRT で復元する。NTT が 1 回少ない分 convolution_ll より速い。
/// @warning 真値が MOD1 * MOD3 (約 3.5e17) 未満であること。畳み込み長 L について
///          各係数は高々 (max|a_i|)*(max|b_j|)*L になるので、これがこの上限を超えない
///          範囲でのみ使う (例: 各係数が 10^5 未満なら長さ 2^24 まで安全)。
///          係数は非負であること (CRT 復元は [0, MOD1*MOD3) を返す)。
/// @note 畳み込み後の長さは 2^24 (約 1.6e7) 以下でなければならない。
/// @param a 入力多項式の係数列
/// @param b 入力多項式の係数列
/// @return std::vector<std::int64_t> a と b の畳み込み (長さ a.size() + b.size() - 1)
/// @complexity 出力長を $N$ として $O(N\log N)$
std::vector<std::int64_t> convolution_ll2(const std::vector<std::int64_t> &a, const std::vector<std::int64_t> &b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};

    using C = internal::convolution_mod_constants;
    assert(n + m - 1 <= (1 << C::MAX_AB_BIT));
    // MOD3 を法とした MOD1 の逆元 (CRT 復元用)。
    static constexpr std::int64_t inv1 = internal::inv_gcd(C::MOD1, C::MOD3).second;

    auto c1 = convolution<C::MOD1>(a, b);
    auto c3 = convolution<C::MOD3>(a, b);

    std::vector<std::int64_t> c(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) {
        // x ≡ c1 (mod MOD1), x ≡ c3 (mod MOD3) を満たす [0, MOD1*MOD3) の値を求める。
        // x = c1 + MOD1 * t, t = (c3 - c1) * inv1 mod MOD3。
        std::int64_t t = (c3[i] - c1[i]) % (std::int64_t)C::MOD3;
        if (t < 0) t += (std::int64_t)C::MOD3;
        t = (std::int64_t)((__int128)t * inv1 % (std::int64_t)C::MOD3);
        c[i] = c1[i] + (std::int64_t)C::MOD1 * t;
    }

    return c;
}

/// @brief 任意 mod 畳み込み (3 つの NTT + Garner 法)
/// @details 3 つの NTT-friendly 素数で畳み込み、Garner 法で復元した値を mod で取る。
///          mod は NTT-friendly でなくてもよい。
/// @warning 各係数は [0, mod) の非負整数であること。Garner 復元値を mod で割った
///          剰余を返すため、負値や mod 以上の値を渡すと正しい結果にならない
///          (真値を mod 還元したい場合は convolution_ll を使うこと)。
/// @note 畳み込み後の長さは 2^24 (約 1.6e7) 以下でなければならない。
/// @tparam mod 出力を取る法 (既定: 998244353)
/// @tparam T 整数型 (std::integral)
/// @param a 入力多項式の係数列
/// @param b 入力多項式の係数列
/// @return std::vector<T> a と b の畳み込みを mod で取った値 (長さ a.size() + b.size() - 1)
/// @see https://math314.hateblo.jp/entry/2015/05/07/014908
/// @see https://asako.growi.cloud/compro/NTT
/// @complexity 出力長を $N$ として $O(N\log N)$
template <unsigned int mod = 998244353, std::integral T>
std::vector<T> convolution_mod(const std::vector<T> &a, const std::vector<T> &b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};

    using C = internal::convolution_mod_constants;
    static constexpr __uint128_t M1M2M3 = (__uint128_t)C::MOD1 * C::MOD2 * C::MOD3;
    assert(n + m - 1 <= (1 << C::MAX_AB_BIT));

    auto c1 = convolution<C::MOD1>(a, b);
    auto c2 = convolution<C::MOD2>(a, b);
    auto c3 = convolution<C::MOD3>(a, b);

    std::vector<T> c(n + m - 1);
    for (int i = 0; i < n + m - 1; ++i) {
        __uint128_t x = (c1[i] * C::i1) % C::MOD1 * (__uint128_t)C::M2M3;
        x += (c2[i] * C::i2) % C::MOD2 * (__uint128_t)C::M1M3;
        if (x >= M1M2M3) x -= M1M2M3;
        x += (c3[i] * C::i3) % C::MOD3 * (__uint128_t)C::M1M2;
        if (x >= M1M2M3) x -= M1M2M3;
        c[i] = x % mod;
    }

    return c;
}
