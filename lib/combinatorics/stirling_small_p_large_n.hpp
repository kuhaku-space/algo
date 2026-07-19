#pragma once
#include <cassert>
#include <cstdint>
#include <vector>

/// @brief 第1種・第2種スターリング数 mod 小さい素数 p を、n, k が巨大（~1e18）でも求める
// (x)_n ≡ (x^p-x)^q (x)_r (mod p)（n=qp+r, Fermat の小定理 x^p≡x による）と、
// その双対にあたる x^n の (x)_k 基底展開の周期性を利用する。
// 前計算 O(p^2)、クエリ 1 回あたり O(log_p n)。
struct StirlingSmallPLargeN {
    explicit StirlingSmallPLargeN(unsigned p) : p_(p), fact(p), finv(p), s1_rows(p), s2_rows(p) {
        assert(p >= 2);
        fact[0] = 1;
        for (unsigned i = 1; i < p_; ++i) fact[i] = (unsigned)((std::uint64_t)fact[i - 1] * i % p_);
        finv[p_ - 1] = mod_pow(fact[p_ - 1], p_ - 2);
        for (unsigned i = p_ - 1; i >= 1; --i) finv[i - 1] = (unsigned)((std::uint64_t)finv[i] * i % p_);

        // s(i,j) = s(i-1,j-1) - (i-1) s(i-1,j)
        s1_rows[0] = {1};
        for (unsigned i = 1; i < p_; ++i) {
            s1_rows[i].assign(i + 1, 0);
            for (unsigned j = 0; j <= i; ++j) {
                std::uint64_t v = 0;
                if (j > 0) v += s1_rows[i - 1][j - 1];
                if (j < i) v += (std::uint64_t)(p_ - (i - 1) % p_) % p_ * s1_rows[i - 1][j] % p_;
                s1_rows[i][j] = (unsigned)(v % p_);
            }
        }

        // S(i,j) = S(i-1,j-1) + j S(i-1,j)
        s2_rows[0] = {1};
        for (unsigned i = 1; i < p_; ++i) {
            s2_rows[i].assign(i + 1, 0);
            for (unsigned j = 0; j <= i; ++j) {
                std::uint64_t v = 0;
                if (j > 0) v += s2_rows[i - 1][j - 1];
                if (j < i) v += (std::uint64_t)j * s2_rows[i - 1][j] % p_;
                s2_rows[i][j] = (unsigned)(v % p_);
            }
        }
    }

    // s(n,k) mod p（符号付き第1種）
    unsigned stirling1(std::int64_t n, std::int64_t k) const {
        if (k < 0 || k > n) return 0;
        std::int64_t i = n / (std::int64_t)p_;
        std::int64_t j = n % (std::int64_t)p_;
        if (i > k) return 0;
        std::int64_t d = (std::int64_t)p_ - 1;
        std::int64_t a = (k - i) / d;
        std::int64_t b = (k - i) % d;
        if (b == 0 && j > 0) {
            b += d;
            a -= 1;
        }
        if (a < 0 || i < a || b > j) return 0;
        unsigned x = binom_lucas(i, a);
        unsigned y = s1_rows[(std::size_t)j][(std::size_t)b];
        unsigned res = (unsigned)((std::uint64_t)x * y % p_);
        if ((i + a) % 2 != 0 && res) res = p_ - res;
        return res;
    }

    // S(n,k) mod p（第2種）
    unsigned stirling2(std::int64_t n, std::int64_t k) const {
        if (k < 0 || k > n) return 0;
        if (n < (std::int64_t)p_) return s2_rows[(std::size_t)n][(std::size_t)k];
        std::int64_t i = k / (std::int64_t)p_;
        std::int64_t j = k % (std::int64_t)p_;
        if (n < i) return 0;
        std::int64_t d = (std::int64_t)p_ - 1;
        std::int64_t a = (n - i) / d;
        std::int64_t b = (n - i) - d * a;
        if (b == 0) {
            b += d;
            a -= 1;
        }
        if (a < 0 || j > b) return 0;
        if (b < d) return (unsigned)((std::uint64_t)binom_lucas(a, i) * s2_rows[(std::size_t)b][(std::size_t)j] % p_);
        if (j == 0) return binom_lucas(a, i - 1);
        return (unsigned)((std::uint64_t)binom_lucas(a, i) * s2_rows[(std::size_t)d][(std::size_t)j] % p_);
    }

  private:
    unsigned p_;
    std::vector<unsigned> fact, finv;
    std::vector<std::vector<unsigned>> s1_rows, s2_rows;

    unsigned mod_pow(unsigned base, unsigned exp) const {
        std::uint64_t res = 1, b = base % p_;
        while (exp) {
            if (exp & 1) res = res * b % p_;
            b = b * b % p_;
            exp >>= 1;
        }
        return (unsigned)res;
    }

    // 0 <= n,k < p の範囲での C(n,k) mod p
    unsigned binom_small(unsigned n, unsigned k) const {
        if (k > n) return 0;
        return (unsigned)((std::uint64_t)fact[n] * finv[k] % p_ * finv[n - k] % p_);
    }

    // Lucas の定理による C(n,k) mod p（n,k は巨大でもよい）
    unsigned binom_lucas(std::int64_t n, std::int64_t k) const {
        if (k < 0 || k > n) return 0;
        std::uint64_t res = 1;
        while (k > 0) {
            unsigned ni = (unsigned)(n % p_), ki = (unsigned)(k % p_);
            if (ki > ni) return 0;
            res = res * binom_small(ni, ki) % p_;
            n /= p_;
            k /= p_;
        }
        return (unsigned)res;
    }
};
