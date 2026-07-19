#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <vector>
#include "math/modint.hpp"

/// @brief 二項係数・階乗・順列・多項係数・重複組合せ
template <internal::modint mint = modint998>
struct Combinatorics {
    Combinatorics() : fact_table(), inv_table(), finv_table() {}

    mint fact(int x) {
        assert(x >= 0);
        init(x);
        return fact_table[x];
    }

    mint finv(int x) {
        assert(x >= 0);
        init(x);
        return finv_table[x];
    }

    // n が table_limit を超える場合はテーブルを持たず binom_direct() に委譲する
    mint binom(std::int64_t n, std::int64_t k) {
        if (n < k || n < 0 || k < 0) return 0;
        if (n <= table_limit) {
            init((int)n);
            return fact_table[n] * finv_table[k] * finv_table[n - k];
        }
        return binom_direct(n, std::min(k, n - k));
    }

    // n が table_limit を超える場合はテーブルを持たず perm_direct() に委譲する
    mint perm(std::int64_t n, std::int64_t k) {
        if (n < k || n < 0 || k < 0) return 0;
        if (n <= table_limit) {
            init((int)n);
            return fact_table[n] * finv_table[n - k];
        }
        return perm_direct(n, k);
    }

    // 多項係数 n! / (k[0]! k[1]! ... k[r-1]!)（sum(k) == n）
    mint multinomial(int n, const std::vector<int> &ks) {
        assert(n >= 0);
        int sum = 0;
        for (int k : ks) {
            assert(k >= 0);
            sum += k;
        }
        assert(sum == n);
        init(n);
        mint res = fact_table[n];
        for (int k : ks) res *= finv_table[k];
        return res;
    }

    // 重複組合せ（n 種類から重複を許して k 個選ぶ場合の数）nHk = C(n+k-1, k)
    mint multiset(std::int64_t n, std::int64_t k) {
        if (n < 0 || k < 0) return 0;
        if (n == 0) return k == 0 ? 1 : 0;
        return binom(n + k - 1, k);
    }

    // Lucas の定理: mod が素数のとき n, k が mod 程度まで巨大でも C(n,k) mod を計算する
    // （base-mod の各桁 n_i, k_i < mod での binom() に帰着。mod 自体が大きいと binom_direct
    // の O(min(k_i, n_i-k_i)) が支配的になり実用的でなくなる点に注意）
    mint binom_lucas(std::int64_t n, std::int64_t k) {
        assert(mint::is_prime_mod());
        if (n < k || n < 0 || k < 0) return 0;
        mint res = 1;
        while (k > 0) {
            std::int64_t ni = n % mod, ki = k % mod;
            if (ki > ni) return 0;
            res *= binom(ni, ki);
            n /= mod;
            k /= mod;
        }
        return res;
    }

  private:
    // テーブルを確保する n の上限（超えると direct()/perm_direct() にフォールバック）
    static constexpr std::int64_t table_limit = 20'000'000;
    static constexpr int mod = mint::mod();
    std::vector<mint> fact_table, inv_table, finv_table;

    mint binom_direct(std::int64_t n, std::int64_t k) const {
        if (n < k || n < 0 || k < 0) return 0;
        if (n - k < k) k = n - k;
        mint res = 1;
        for (std::int64_t i = 0; i < k; ++i) {
            res *= n - i;
            res /= i + 1;
        }
        return res;
    }

    mint perm_direct(std::int64_t n, std::int64_t k) const {
        if (n < k || n < 0 || k < 0) return 0;
        mint res = 1;
        for (std::int64_t i = 0; i < k; ++i) res *= n - i;
        return res;
    }

    void init(int n) {
        if ((int)fact_table.size() > n) return;
        int m = fact_table.size();
        fact_table.resize(n + 1);
        for (int i = m; i <= n; ++i) {
            if (i == 0) fact_table[i] = 1;
            else fact_table[i] = fact_table[i - 1] * i;
        }
        inv_table.resize(n + 1);
        for (int i = m; i <= n; ++i) {
            if (i <= 1) inv_table[i] = 1;
            else inv_table[i] = -inv_table[mod % i] * (mod / i);
        }
        finv_table.resize(n + 1);
        for (int i = m; i <= n; ++i) {
            if (i == 0) finv_table[i] = 1;
            else finv_table[i] = finv_table[i - 1] * inv_table[i];
        }
    }
};
