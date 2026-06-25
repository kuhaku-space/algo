#pragma once
#include <cmath>
#include <functional>
#include <utility>
#include <vector>

/// @brief f(p) の素数項 coef * p^pw を表す
///
/// prefix(x) = Σ_{i=1}^{x} i^pw（pw 乗和の閉じた式）を渡す。
template <class T>
struct Min25Term {
    T coef;
    int pw;
    std::function<T(long long)> prefix;
};

/// @brief Min_25 篩：乗法的関数の累積和を O(N^{3/4} / log N) で計算する
///
/// 素数 p での値 f(p) が p の多項式 Σ coef·p^pw で表せる乗法的関数 f について、
/// S(N) = Σ_{i=1}^{N} f(i) を求める。素数冪での値 f(p^e) は fpe で与える。
/// @tparam T 値の型（modint 等）
/// @tparam Fpe (long long p, int e, long long pe) -> T。pe == p^e で f(p^e) を返す。
template <class T, class Fpe>
struct Min25Sieve {
    Min25Sieve(long long n, std::vector<Min25Term<T>> terms, Fpe fpe) : N(n), fpe(std::move(fpe)) { build(terms); }

    /// @brief S(N) = Σ_{i=1}^{N} f(i)
    T sum() { return N <= 0 ? T(0) : T(1) + rec(N, 0); }

  private:
    long long N, sq = 0;
    std::vector<long long> primes;
    // small[v] = Σ_{p<=v} f(p)（v <= sq）、large[i] = Σ_{p<=N/i} f(p)
    std::vector<T> small, large;
    Fpe fpe;

    // x = ⌊N/i⌋ における Σ_{p<=x} f(p)
    T prime_sum(long long x) const { return x <= sq ? small[x] : large[N / x]; }

    void build(std::vector<Min25Term<T>> &terms) {
        sq = (long long)std::sqrt((long double)N);
        while (sq > 0 && sq * sq > N) --sq;
        while ((sq + 1) * (sq + 1) <= N) ++sq;

        std::vector<bool> composite(sq + 1, false);
        for (long long i = 2; i <= sq; ++i) {
            if (composite[i]) continue;
            primes.emplace_back(i);
            for (long long j = i * i; j <= sq; j += i) composite[j] = true;
        }

        const int m = (int)terms.size();
        // gs[t][v] = Σ_{i<=v} i^pw（合成数を篩い落とすと素数のみの和になる）
        std::vector<std::vector<T>> gs(m, std::vector<T>(sq + 1)), gl(m, std::vector<T>(sq + 1));
        for (int t = 0; t < m; ++t) {
            for (long long v = 1; v <= sq; ++v) gs[t][v] = terms[t].prefix(v) - T(1);
            for (long long i = 1; i <= sq; ++i) gl[t][i] = terms[t].prefix(N / i) - T(1);
        }

        for (long long p : primes) {
            const long long p2 = p * p;
            if (p2 > N) break;
            const long long lim = std::min(N / p2, sq);  // 値 N/i >= p^2 となる i の上限
            for (int t = 0; t < m; ++t) {
                T pk = T(1);
                for (int e = 0; e < terms[t].pw; ++e) pk *= T(p);
                const T psub = gs[t][p - 1];  // 素数 < p の p^pw 和
                auto &Gs = gs[t];
                auto &Gl = gl[t];
                // 大きい値側（N/i > sq になりうる）を i 昇順 = 値 降順 で更新
                for (long long i = 1; i <= lim; ++i) {
                    const long long d = (N / i) / p;
                    const T sub = (d <= sq) ? Gs[d] : Gl[N / d];
                    Gl[i] -= pk * (sub - psub);
                }
                // 小さい値側を v 降順で更新（v/p < v は未更新の状態を読む）
                for (long long v = sq; v >= p2; --v) Gs[v] -= pk * (Gs[v / p] - psub);
            }
        }

        small.assign(sq + 1, T(0));
        large.assign(sq + 1, T(0));
        for (int t = 0; t < m; ++t) {
            const T c = terms[t].coef;
            for (long long v = 1; v <= sq; ++v) small[v] += c * gs[t][v];
            for (long long i = 1; i <= sq; ++i) large[i] += c * gl[t][i];
        }
    }

    // n 以下で最小素因数が primes[j] 以上の合成数・素数についての f の和（i=1 は含めない）
    T rec(long long n, int j) {
        if (n <= 1) return T(0);
        // i が素数（primes[j] <= p <= n）の寄与
        T res = prime_sum(n) - (j == 0 ? T(0) : prime_sum(primes[j - 1]));
        for (int k = j; k < (int)primes.size() && primes[k] * primes[k] <= n; ++k) {
            const long long p = primes[k];
            long long pe = p;
            for (int e = 1; pe * p <= n; ++e) {
                // f(p^e)·(より大きい素因数からなる部分) ＋ 素数冪 p^{e+1} そのもの
                res += fpe(p, e, pe) * rec(n / pe, k + 1) + fpe(p, e + 1, pe * p);
                pe *= p;
            }
        }
        return res;
    }
};

/// @brief Min_25 篩で S(N) = Σ_{i=1}^{N} f(i) を計算する（型推論用ヘルパ）
template <class T, class Fpe>
T min25_sum(long long n, std::vector<Min25Term<T>> terms, Fpe fpe) {
    return Min25Sieve<T, Fpe>(n, std::move(terms), std::move(fpe)).sum();
}
