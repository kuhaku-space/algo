#pragma once
#include <cassert>
#include <cstdint>
#include <vector>

/// @brief 第1種スターリング数（符号付き）mod 小さい素数 p を、n が巨大（~1e18）でも求める
// n = qp + r (0 <= r < p) と分解すると Fermat の小定理 x^p ≡ x (mod p) と
// 因数定理から (x)_n ≡ (x^p - x)^q (x)_r (mod p) が成り立つ（(x)_m は下降階乗）。
// (x^p-x)^q = x^q (x^{p-1}-1)^q を二項展開して (x)_r の係数 s(r, b) と合わせると
//   s(n, k) = sum_{(a,b): (p-1)a+b = k-q, 0<=a<=q, 0<=b<=r} (-1)^{q-a} C(q,a) s(r,b)
// が成り立つ。b は mod (p-1) で高々2通りに絞れるので、前計算 O(p^2) の後
// 1 クエリ O(log_p n) で計算できる。
struct StirlingSmallPLargeN {
    explicit StirlingSmallPLargeN(unsigned p) : p_(p), fact(p), finv(p), s1_rows(p) {
        assert(p >= 2);
        fact[0] = 1;
        for (unsigned i = 1; i < p_; ++i) fact[i] = (unsigned)((std::uint64_t)fact[i - 1] * i % p_);
        finv[p_ - 1] = mod_pow(fact[p_ - 1], p_ - 2);
        for (unsigned i = p_ - 1; i >= 1; --i) finv[i - 1] = (unsigned)((std::uint64_t)finv[i] * i % p_);

        s1_rows[0] = {1};
        for (unsigned r = 1; r < p_; ++r) {
            s1_rows[r].assign(r + 1, 0);
            for (unsigned b = 0; b <= r; ++b) {
                std::uint64_t v = 0;
                if (b > 0) v += s1_rows[r - 1][b - 1];
                // s(r,b) = s(r-1,b-1) - (r-1)*s(r-1,b)（b==r のとき s(r-1,b) は範囲外＝0）
                if (b < r) v += (std::uint64_t)(p_ - (unsigned)((r - 1) % p_)) % p_ * s1_rows[r - 1][b] % p_;
                s1_rows[r][b] = (unsigned)(v % p_);
            }
        }
    }

    // s(n,k) mod p
    unsigned stirling1(std::uint64_t n, std::uint64_t k) const {
        if (k > n) return 0;
        std::uint64_t q = n / p_;
        unsigned r = (unsigned)(n % p_);
        unsigned d = p_ - 1;
        unsigned res = 0;
        if (d == 0) {
            // p_ >= 2 が前提なので到達しない
            return 0;
        }
        std::int64_t base = (std::int64_t)k - (std::int64_t)q;
        std::int64_t b0 = ((base % (std::int64_t)d) + (std::int64_t)d) % (std::int64_t)d;
        for (std::int64_t b : {b0, b0 + (std::int64_t)d}) {
            if (b < 0 || b > (std::int64_t)r) continue;
            std::int64_t numerator = base - b;
            std::int64_t a = numerator / (std::int64_t)d;
            if (a < 0 || (std::uint64_t)a > q) continue;
            unsigned c = binom_lucas(q, (std::uint64_t)a);
            if (c == 0) continue;
            unsigned term = (unsigned)((std::uint64_t)s1_rows[r][b] * c % p_);
            std::uint64_t exp = q - (std::uint64_t)a;
            if (exp & 1) term = (p_ - term) % p_;
            res = (unsigned)(((std::uint64_t)res + term) % p_);
        }
        return res;
    }

  private:
    unsigned p_;
    std::vector<unsigned> fact, finv;
    std::vector<std::vector<unsigned>> s1_rows;

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
    unsigned binom_lucas(std::uint64_t n, std::uint64_t k) const {
        if (k > n) return 0;
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
