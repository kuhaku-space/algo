#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>
#include "fft/formal_power_series.hpp"
#include "math/modint.hpp"

namespace internal {

// 特性多項式を法とした x^n mod f を二乗法で求めるきたまさ法の本体 (汎用環版, O(k^2 log n))。
// 漸化式 a_i = sum_{j=1}^{k} d[j-1] a_{i-j} に対し f(x) = x^k - sum_j d[j-1] x^{k-1-j}。
// x^k ≡ sum_j d[k-1-j] x^j (mod f) を使い、長さ <= 2k-1 の積を毎回 f で割って長さ k に落とす。
template <class T>
T kitamasa_naive(const std::vector<T> &a, const std::vector<T> &d, std::int64_t n) {
    const int k = (int)d.size();

    // xk[j] = x^k の x^j 係数 = d[k-1-j]。
    std::vector<T> xk(k);
    for (int j = 0; j < k; ++j) xk[j] = d[k - 1 - j];

    // 長さ 2k-1 の多項式を x^{>=k} を順に潰して長さ k の剰余へ落とす。
    auto reduce = [&](std::vector<T> &p) {
        for (int i = (int)p.size() - 1; i >= k; --i) {
            T c = p[i];
            if (c == T()) continue;
            p[i] = T();
            for (int j = 0; j < k; ++j) p[i - k + j] += c * xk[j];
        }
        p.resize(k);
    };
    auto mulmod = [&](const std::vector<T> &p, const std::vector<T> &q) {
        std::vector<T> r(p.size() + q.size() - 1, T());
        for (int i = 0; i < (int)p.size(); ++i)
            for (int j = 0; j < (int)q.size(); ++j) r[i + j] += p[i] * q[j];
        reduce(r);
        return r;
    };

    // res = 1, base = x (k=1 なら x ≡ d[0])。
    std::vector<T> res(k, T());
    res[0] = T(1);
    std::vector<T> base(k, T());
    if (k == 1) base[0] = d[0];
    else base[1] = T(1);
    while (n > 0) {
        if (n & 1) res = mulmod(res, base);
        n >>= 1;
        if (n) base = mulmod(base, base);
    }
    T ans{};
    for (int i = 0; i < k; ++i) ans += res[i] * a[i];
    return ans;
}

}  // namespace internal

/// @brief きたまさ法 (汎用環版, O(k^2 log n))
/// @details 線形漸化式 a_i = sum_{j=1}^{k} d[j-1] a_{i-j} (i >= k) の第 n 項を、
///          特性多項式 f(x) = x^k - sum_j d[j-1] x^{k-1-j} を法とした x^n mod f の
///          二乗法で求める。任意の可換環 T に対応 (modint 以外でも可)。
/// @tparam T 可換環 (加減乗算と T(0)/T(1) を持つ)
/// @param a 初項 a_0, ..., a_{k-1}
/// @param d 漸化式の係数 d_1, ..., d_k (a_i = d_1 a_{i-1} + ... + d_k a_{i-k})
/// @param n 求める項の番号
/// @return T a_n
template <class T>
requires(!internal::static_modint_c<T>)
T kitamasa(const std::vector<T> &a, const std::vector<T> &d, std::int64_t n) {
    assert(a.size() == d.size());
    const int k = (int)d.size();
    if (n < k) return a[n];
    return internal::kitamasa_naive(a, d, n);
}

/// @brief きたまさ法 (NTT 版, static_modint, O(M(k) log n))
/// @details 汎用版と同じく x^n mod f を二乗法で求めるが、多項式積を NTT 畳み込み、
///          剰余を NTT ベースの多項式除算で行う。k が小さいうちは O(k^2) の汎用版に
///          フォールバックして NTT の定数倍を避ける。
/// @tparam mint NTT-friendly な static modint
/// @param a 初項 a_0, ..., a_{k-1}
/// @param d 漸化式の係数 d_1, ..., d_k
/// @param n 求める項の番号
/// @return mint a_n
template <internal::static_modint_c mint>
mint kitamasa(const std::vector<mint> &a, const std::vector<mint> &d, std::int64_t n) {
    assert(a.size() == d.size());
    const int k = (int)d.size();
    if (n < k) return a[n];

    // k が小さいと NTT の定数倍が勝てないので汎用 O(k^2) 版へ。
    static constexpr int KITAMASA_NTT_THRESHOLD = 64;
    if (k <= KITAMASA_NTT_THRESHOLD) return internal::kitamasa_naive(a, d, n);

    // 特性多項式 f (低次->高次, モニック, 末尾 0 なし): f[j] = -d[k-1-j], f[k] = 1。
    std::vector<mint> f(k + 1);
    for (int j = 0; j < k; ++j) f[j] = -d[k - 1 - j];
    f[k] = 1;

    auto mulmod = [&](const std::vector<mint> &p, const std::vector<mint> &q) {
        return fps::internal_fps::mod_monic(fps::internal_fps::conv_auto(p, q), f);
    };

    std::vector<mint> res = {mint(1)}, base = {mint(0), mint(1)};  // res = 1, base = x
    while (n > 0) {
        if (n & 1) res = mulmod(res, base);
        n >>= 1;
        if (n) base = mulmod(base, base);
    }
    res.resize(k);
    mint ans{};
    for (int i = 0; i < k; ++i) ans += res[i] * a[i];
    return ans;
}
