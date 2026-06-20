#pragma once
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>
#include "fft/ntt.hpp"
#include "fft/ntt_avx2.hpp"

namespace internal {

// Bostan-Mori の 1 ステップ (スカラ NTT, DFT 使い回し)。p, q は通常表現。
// q(-x) (= 奇数次のみ符号反転) の順変換を p*q(-x) と q*q(-x) で共有し、
// 素朴な 2 畳み込み (6 NTT) を 3 順変換 + 2 逆変換に削減する。
// odd=true で次の p に奇数次成分を、false で偶数次成分を採る。
template <internal::static_modint_c mint>
void bostan_mori_step(std::vector<mint> &p, std::vector<mint> &q, bool odd) {
    int np = (int)p.size(), nq = (int)q.size();

    std::vector<mint> q_minus = q;
    for (int i = 1; i < nq; i += 2) q_minus[i] = -q_minus[i];

    int lp = np + nq - 1, lq = 2 * nq - 1;
    if (std::min(np, nq) <= CONVOLUTION_NAIVE_THRESHOLD) {
        p = convolution(p, q_minus);
        q = convolution(q, q_minus);
    } else {
        int z = std::bit_ceil<unsigned>((unsigned)lq);
        std::vector<mint> P(z), Q(z), QM(z);
        for (int i = 0; i < np; ++i) P[i] = p[i];
        for (int i = 0; i < nq; ++i) Q[i] = q[i], QM[i] = q_minus[i];
        internal::butterfly(P);
        internal::butterfly(Q);
        internal::butterfly(QM);
        for (int i = 0; i < z; ++i) P[i] *= QM[i];
        for (int i = 0; i < z; ++i) Q[i] *= QM[i];
        internal::butterfly_inv(P);
        internal::butterfly_inv(Q);
        mint iz = mint(z).inv();
        for (int i = 0; i < lp; ++i) P[i] *= iz;
        for (int i = 0; i < lq; ++i) Q[i] *= iz;
        P.resize(lp);
        Q.resize(lq);
        p = std::move(P);
        q = std::move(Q);
    }

    std::vector<mint> rp((lp + (odd ? 0 : 1)) / 2), rq((lq + 1) / 2);
    for (int i = odd ? 1 : 0, k = 0; i < lp; i += 2, ++k) rp[k] = p[i];
    for (int i = 0, k = 0; i < lq; i += 2, ++k) rq[k] = q[i];
    p = std::move(rp);
    q = std::move(rq);
}

}  // namespace internal

/// @brief Bostan-Mori 法
/// @details 有理形式的冪級数 p(x)/q(x) の x^n の係数を O(M(d) log n) で求める
///          (d = deg q, M はサイズ d の畳み込みコスト)。各ステップで q(-x) の順変換を
///          共有し、AVX2 が使える NTT-friendly な mint なら Montgomery + AVX2 NTT を使う。
/// @tparam mint NTT-friendly な static modint
/// @param p 分子の係数列
/// @param q 分母の係数列 (q[0] != 0)
/// @param n 求める項の番号 (n < 0 なら 0)
/// @return mint p(x)/q(x) の x^n の係数
template <internal::static_modint_c mint>
mint bostan_mori(std::vector<mint> p, std::vector<mint> q, std::int64_t n) {
    if (n < 0) return 0;

    constexpr unsigned int mod = (unsigned int)mint::mod();
    if constexpr (mod < (1u << 30)) {
        // AVX2 が使えるなら Montgomery + AVX2 NTT 版に振り分ける。
        if (mint::is_prime_mod() && internal::has_avx2()) {
            std::vector<std::uint32_t> up(p.size()), uq(q.size());
            for (std::size_t i = 0; i < p.size(); ++i) up[i] = (std::uint32_t)p[i].val();
            for (std::size_t i = 0; i < q.size(); ++i) uq[i] = (std::uint32_t)q[i].val();
            return mint::raw((int)internal::avx2::bostan_mori<mod>(std::move(up), std::move(uq), n));
        }
    }

    while (n > 0) {
        if ((int)p.size() >= (int)q.size()) p.resize(q.size() - 1);
        internal::bostan_mori_step(p, q, n & 1);
        n >>= 1;
    }
    return p[0] / q[0];
}

/// @brief 線形漸化式の N 項目
/// @details a_i = sum_{j=1}^d c_j a_{i-j} (i >= d) の第 n 項を Bostan-Mori 法で求める。
/// @tparam mint NTT-friendly な static modint
/// @param a 初項 a_0, ..., a_{d-1}
/// @param c 漸化式の係数 c_1, ..., c_d
/// @param n 求める項の番号
/// @return mint a_n
template <internal::static_modint_c mint>
mint kth_term(std::vector<mint> a, std::vector<mint> c, std::int64_t n) {
    assert(a.size() == c.size());
    int d = a.size();
    if (n < d) return a[n];
    std::vector<mint> q(d + 1);
    q[0] = 1;
    for (int i = 0; i < d; ++i) q[i + 1] = -c[i];
    std::vector<mint> p = convolution(a, q);
    p.resize(d);
    return bostan_mori(p, q, n);
}
