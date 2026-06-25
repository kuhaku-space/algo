#pragma once
#include <cstdint>
#include <vector>

/// @brief 乗法的関数の値を線形篩で一括計算する
///
/// 乗法的関数 f（f(1)=1, gcd(m,n)=1 で f(mn)=f(m)f(n)）の f(1), ..., f(n) を
/// O(n) で構築する。素数冪での値 f(p^k) を返す callable を渡す。
/// @tparam T 値の型（modint や整数型）
/// @tparam F (int p, int k, int pk) -> T を満たす callable。pk == p^k。
/// @param n 上限（n >= 0）
/// @param fpk f(p^k) を返す関数。p は素数、k >= 1、pk = p^k。
/// @return f[i] = f(i)（0 <= i <= n）。f[0] = T()、f[1] = T(1)。
template <class T, class F>
std::vector<T> multiplicative_table(int n, F fpk) {
    std::vector<T> f(n + 1, T());
    if (n >= 1) f[1] = T(1);
    std::vector<int> primes;
    std::vector<bool> composite(n + 1, false);
    // cnt[i]: i の最小素因数 p の指数、pk[i]: p^cnt[i]
    std::vector<int> cnt(n + 1, 0), pk(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        if (!composite[i]) {
            primes.emplace_back(i);
            cnt[i] = 1, pk[i] = i;
            f[i] = fpk(i, 1, i);
        }
        for (int p : primes) {
            const std::int64_t ip = (std::int64_t)i * p;
            if (ip > n) break;
            const int j = (int)ip;
            composite[j] = true;
            if (i % p == 0) {
                // p は i の最小素因数。指数が 1 増える。
                cnt[j] = cnt[i] + 1, pk[j] = pk[i] * p;
                // i = pk[i] * (i / pk[i])、後者は p と互いに素。
                f[j] = f[i / pk[i]] * fpk(p, cnt[j], pk[j]);
                break;
            }
            // gcd(i, p) = 1。
            cnt[j] = 1, pk[j] = p;
            f[j] = f[i] * f[p];
        }
    }
    return f;
}

/// @brief オイラーのトーシェント関数 φ(1), ..., φ(n)
///
/// φ(p^k) = p^k - p^(k-1)。
std::vector<int> euler_phi_table(int n) {
    return multiplicative_table<int>(n, [](int p, int, int pk) { return pk - pk / p; });
}

/// @brief メビウス関数 μ(1), ..., μ(n)
///
/// μ(p) = -1、μ(p^k) = 0 (k >= 2)。
std::vector<int> mobius_table(int n) {
    return multiplicative_table<int>(n, [](int, int k, int) { return k == 1 ? -1 : 0; });
}

/// @brief 約数の個数 σ_0(1), ..., σ_0(n)
///
/// σ_0(p^k) = k + 1。
std::vector<int> divisor_count_table(int n) {
    return multiplicative_table<int>(n, [](int, int k, int) { return k + 1; });
}

/// @brief 約数の総和 σ_1(1), ..., σ_1(n)
///
/// σ_1(p^k) = 1 + p + ... + p^k。
std::vector<std::int64_t> divisor_sum_table(int n) {
    return multiplicative_table<std::int64_t>(n, [](int p, int k, int) {
        std::int64_t sum = 1, cur = 1;
        for (int i = 0; i < k; ++i) sum += (cur *= p);
        return sum;
    });
}
