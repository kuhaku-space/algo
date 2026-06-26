#pragma once
#include <cmath>
#include <cstdint>
#include <functional>
#include <utility>
#include <vector>

namespace internal {

// 固定除数 p に対する floor(a / p) を、事前計算した M = floor(2^64 / p) で
// 乗算に置き換えて求める（Barrett 風）。a, p は非負で a < 2^63、p >= 2。
// M = floor(2^64/p) >= 2^64/p - 1 より q は真値か真値-1 なので補正は 1 回で十分。
inline long long fast_div(long long a, long long p, std::uint64_t M) {
    std::uint64_t q = (std::uint64_t)(((__uint128_t)M * (std::uint64_t)a) >> 64);
    if ((long long)(a - (long long)q * p) >= p) ++q;
    return (long long)q;
}

}  // namespace internal

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
    std::vector<std::uint64_t> inv_p;  // inv_p[k] = ⌊2^64 / primes[k]⌋（Barrett 用）
    std::vector<T> fp1, fp2;           // fp1[k]=f(primes[k])、fp2[k]=f(primes[k]^2)（再帰のホットパス用）
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
        inv_p.resize(primes.size());
        fp1.resize(primes.size());
        fp2.resize(primes.size());
        for (std::size_t k = 0; k < primes.size(); ++k) {
            const long long p = primes[k];
            inv_p[k] = (std::uint64_t)((__uint128_t(1) << 64) / (std::uint64_t)p);
            fp1[k] = fpe(p, 1, p);
            fp2[k] = fpe(p, 2, p * p);
        }

        std::vector<long long> quot(sq + 1);
        for (long long i = 1; i <= sq; ++i) quot[i] = N / i;

        const int m = (int)terms.size();
        // 項をインタリーブした flat 配列で持つ（同じ値 v の全項が連続 → キャッシュ効率）。
        // gs[v*m + t] = Σ_{i<=v} i^pw（合成数を篩い落とすと素数のみの和になる）
        std::vector<T> gs((sq + 1) * m, T(0)), gl((sq + 1) * m, T(0));
        for (int t = 0; t < m; ++t) {
            for (long long v = 1; v <= sq; ++v) gs[v * m + t] = terms[t].prefix(v) - T(1);
            for (long long i = 1; i <= sq; ++i) gl[i * m + t] = terms[t].prefix(quot[i]) - T(1);
        }

        // 項ごとの p^pw と「素数 < p の p^pw 和」。インデックス計算を全項で共有するため
        // ループは値（i, v）を外側にして全項をまとめて更新する（除算の重複を避ける）。
        // pw==0（π(x) 相当）の項は pk==1 なので乗算を省く。
        std::vector<T> pk(m), psub(m);
        std::vector<char> nomul(m);
        for (int t = 0; t < m; ++t) nomul[t] = (terms[t].pw == 0);
        for (long long p : primes) {
            const long long p2 = p * p;
            if (p2 > N) break;
            const long long lim = std::min(N / p2, sq);  // 値 N/i >= p^2 となる i の上限
            for (int t = 0; t < m; ++t) {
                T v = T(1);
                for (int e = 0; e < terms[t].pw; ++e) v *= T(p);
                pk[t] = v;
                psub[t] = gs[(p - 1) * m + t];  // 素数 < p の p^pw 和
            }
            // 大きい値側（N/i > sq になりうる）を i 昇順 = 値 降順 で更新
            for (long long i = 1; i <= lim; ++i) {
                const long long d = quot[i] / p;
                const T *src = (d <= sq) ? &gs[d * m] : &gl[(N / d) * m];
                T *dst = &gl[i * m];
                for (int t = 0; t < m; ++t) {
                    const T diff = src[t] - psub[t];
                    dst[t] -= nomul[t] ? diff : pk[t] * diff;
                }
            }
            // 小さい値側を v 降順で更新（v/p < v は未更新の状態を読む）
            for (long long v = sq; v >= p2; --v) {
                const T *src = &gs[(v / p) * m];
                T *dst = &gs[v * m];
                for (int t = 0; t < m; ++t) {
                    const T diff = src[t] - psub[t];
                    dst[t] -= nomul[t] ? diff : pk[t] * diff;
                }
            }
        }

        small.assign(sq + 1, T(0));
        large.assign(sq + 1, T(0));
        for (int t = 0; t < m; ++t) {
            const T c = terms[t].coef;
            for (long long v = 1; v <= sq; ++v) small[v] += c * gs[v * m + t];
            for (long long i = 1; i <= sq; ++i) large[i] += c * gl[i * m + t];
        }
    }

    // n 以下で最小素因数が primes[j] 以上の合成数・素数についての f の和（i=1 は含めない）
    // 呼び出しの大半は「葉」（k ループが空回りし prime_sum 差だけ返す）なので、
    // 子が葉になる場合は再帰せずインライン展開して関数呼び出しを省く。
    T rec(long long n, int j) {
        if (n <= 1) return T(0);
        const int sz = (int)primes.size();
        // pref = prime_sum(primes[k-1])（素数順の prefix を持ち回し、葉での配列読みを消す）
        T pref = (j == 0) ? T(0) : prime_sum(primes[j - 1]);
        // i が素数（primes[j] <= p <= n）の寄与
        T res = prime_sum(n) - pref;
        for (int k = j; k < sz; ++k) {
            const long long p = primes[k];
            if (p * p > n) break;
            const std::uint64_t M = inv_p[k];
            const long long np = internal::fast_div(n, p, M);  // n/p。pe*p<=n は pe<=np と同値
            // 子 rec(nq, k+1) が葉になる閾値。次の素数が無ければ常にインライン（nq < n+1）。
            const long long next2 = (k + 1 < sz) ? primes[k + 1] * primes[k + 1] : n + 1;
            long long pe = p;            // p^e
            long long nq = np;           // n/p^e（e=1 で n/p）
            T fe = fp1[k];               // f(p)（事前計算）。持ち回して fpe 呼び出しを減らす
            const T psum_p = pref + fe;  // prime_sum(p) = prime_sum(primes[k-1]) + f(p)
            pref = psum_p;
            // 大半の素数は e=1 で終わる。継続するときだけ nq を更新し無駄な除算を省く。
            for (int e = 1;; ++e) {
                const long long pe1 = pe * p;                          // p^{e+1}（pe <= np より n 以下）
                const T fe1 = (e == 1) ? fp2[k] : fpe(p, e + 1, pe1);  // f(p^{e+1})
                // f(p^e)·(より大きい素因数からなる部分) ＋ 素数冪 p^{e+1} そのもの。
                // nq >= next2 のときだけ非葉なので再帰、それ以外は葉をインライン。
                const T sub = (nq >= next2) ? rec(nq, k + 1) : prime_sum(nq) - psum_p;
                res += fe * sub + fe1;
                if (pe1 > np) break;  // 次の指数 e+1 は p^{e+2} > n となり打ち切り
                pe = pe1, fe = fe1;
                nq = internal::fast_div(nq, p, M);  // n/p^{e+1}
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
