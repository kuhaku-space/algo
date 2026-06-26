#pragma once
#include <cmath>
#include <cstdint>
#include <utility>
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
    // π(n) ≈ n/(ln n - 1.1)。小さい n では分母が非正になり得るので大きいときのみ予約。
    if (n >= 16) primes.reserve((std::size_t)(n / (std::log((double)n) - 1.1)) + 16);
    // low[i] = {最小素因数 p の指数 cnt, p^cnt}。cnt と pk を 1 構造体にまとめると
    // j = i*p への散在書き込みが 1 キャッシュラインに収まり篩が速くなる。pk==0 が
    // 未確定（素数）の印を兼ねるので別途 composite 配列は持たない。
    struct Low {
        int cnt, pk;
    };
    std::vector<Low> low(n + 1, {0, 0});
    for (int i = 2; i <= n; ++i) {
        if (low[i].pk == 0) {  // i は素数
            primes.emplace_back(i);
            low[i] = {1, i};
            f[i] = fpk(i, 1, i);
        }
        const int ci = low[i].cnt, pki = low[i].pk;  // i の最小素因数の指数と冪
        const T fi = f[i];
        for (int p : primes) {
            const std::int64_t ip = (std::int64_t)i * p;
            if (ip > n) break;
            const int j = (int)ip;
            if (i % p == 0) {
                // p は i の最小素因数。指数が 1 増える。i = pki * (i/pki)、後者は p と互いに素。
                low[j] = {ci + 1, pki * p};
                f[j] = f[i / pki] * fpk(p, ci + 1, pki * p);
                break;
            }
            // gcd(i, p) = 1。
            low[j] = {1, p};
            f[j] = fi * f[p];
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

/// @brief 乗法的関数の累積和を劣線形で計算する（杜教筛 / Dirichlet 双曲線法）
///
/// 乗法的関数 f の累積和 S(n) = Σ_{i=1}^{n} f(i) を O(n^{2/3}) で求める。
/// f とディリクレ畳み込み f*g がともに累積和を計算しやすい g を選び、
/// 恒等式 Σ_{i=1}^{m} (f*g)(i) = Σ_{d=1}^{m} g(d) S(⌊m/d⌋) から
/// g(1)S(m) = H(m) - Σ_{d=2}^{m} g(d) S(⌊m/d⌋) を再帰的に解く。
/// @tparam T 値の型（modint や整数型）
/// @tparam Gsum (long long m) -> T。G(m) = Σ_{i=1}^{m} g(i)。
/// @tparam Hsum (long long m) -> T。H(m) = Σ_{i=1}^{m} (f*g)(i)。
template <class T, class Gsum, class Hsum>
struct MultiplicativeSum {
    /// @param n 上限
    /// @param f_prefix f の累積和。f_prefix[k] = Σ_{i=1}^{k} f(i)（k <= threshold）。
    ///   threshold は n^{2/3} 程度を推奨（base case の打ち切り）。
    /// @param g1 g(1)（多くの場合 1）
    /// @param G G(m) = Σ_{i=1}^{m} g(i)
    /// @param H H(m) = Σ_{i=1}^{m} (f*g)(i)
    MultiplicativeSum(long long n, std::vector<T> f_prefix, T g1, Gsum G, Hsum H)
        : n(n), threshold((long long)f_prefix.size() - 1), small(std::move(f_prefix)) {
        // large[i] = S(⌊n/i⌋)。⌊n/i⌋ が閾値超えの i についてのみ持つ。
        const long long L = threshold > 0 ? n / threshold : 0;
        large.assign(L + 1, T());
        const bool g1_one = (g1 == T(1));
        // m = ⌊n/i⌋ 昇順（i 降順）に計算する。各 S(q)（q < m）は small か計算済み large から
        // 引けるので再帰不要・メモ判定不要。葉 q<=threshold は small を直接参照する。
        for (long long i = L; i >= 1; --i) {
            const long long m = n / i;
            if (m <= threshold) continue;  // small で足りる
            T res = H(m);
            T gprev = G(1);  // d-1 = 1 の G 値（次反復の G(d-1) を持ち回す）
            for (long long d = 2, nd; d <= m; d = nd + 1) {
                const long long q = m / d;
                nd = m / q;  // ⌊m/d⌋ == q となる d の最大値
                const T gnd = G(nd);
                const T sq = (q <= threshold) ? small[q] : large[n / q];  // q < m なので算出済み
                res -= (gnd - gprev) * sq;
                gprev = gnd;
            }
            large[i] = g1_one ? res : res / g1;
        }
    }

    /// @brief S(n) = Σ_{i=1}^{n} f(i)
    T sum() const { return get(n); }

    /// @brief S(m) = Σ_{i=1}^{m} f(i)（m <= n、⌊n/i⌋ の形の値）
    T get(long long m) const { return m <= threshold ? small[m] : large[n / m]; }

  private:
    long long n, threshold;
    std::vector<T> small, large;
};

namespace internal {

// n^{2/3} 程度の打ち切り点（base case のサイズ）。正しさは任意の打ち切りで
// 保たれるため近似で十分。n*n のオーバーフローを避けて double で計算する。
inline long long sublinear_threshold(long long n) {
    if (n <= 1) return n < 0 ? 0 : n;
    long long t = (long long)std::cbrt((double)n * (double)n);
    return std::min(n, std::max<long long>(1, t));
}

}  // namespace internal

/// @brief Σ_{i=1}^{n} φ(i) を O(n^{2/3}) で計算する
///
/// φ*1 = Id（恒等関数）より H(m) = m(m+1)/2、g = 1 で杜教筛を回す。
template <class T>
T totient_sum(long long n) {
    if (n <= 0) return T(0);
    long long th = internal::sublinear_threshold(n);
    auto phi = euler_phi_table((int)th);
    std::vector<T> pre(th + 1, T(0));
    for (long long i = 1; i <= th; ++i) pre[i] = pre[i - 1] + T(phi[i]);
    const T inv2 = T(1) / T(2);
    auto G = [](long long m) { return T(m); };
    auto H = [inv2](long long m) { return T(m) * T(m + 1) * inv2; };
    return MultiplicativeSum<T, decltype(G), decltype(H)>(n, std::move(pre), T(1), G, H).sum();
}

/// @brief メルテンス関数 Σ_{i=1}^{n} μ(i) を O(n^{2/3}) で計算する
///
/// μ*1 = ε（単位元）より H(m) = 1、g = 1 で杜教筛を回す。
template <class T>
T mobius_sum(long long n) {
    if (n <= 0) return T(0);
    long long th = internal::sublinear_threshold(n);
    auto mu = mobius_table((int)th);
    std::vector<T> pre(th + 1, T(0));
    for (long long i = 1; i <= th; ++i) pre[i] = pre[i - 1] + T(mu[i]);
    auto G = [](long long m) { return T(m); };
    auto H = [](long long) { return T(1); };
    return MultiplicativeSum<T, decltype(G), decltype(H)>(n, std::move(pre), T(1), G, H).sum();
}
