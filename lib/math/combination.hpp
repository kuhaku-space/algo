#include "_base.hpp"
#include "modint.hpp"

template <int mod>
struct math_mod {
    using mint = ModInt<mod>;
    vector<mint> fac, finv;

    math_mod() {
        _init(3000000);
    }

    void _init(const int64_t n) {
        if (fac.size() > n) return;
        const int m = fac.size();
        fac.resize(n + 1);
        for (int64_t i = m; i <= n; ++i) {
            if (i == 0) fac[i] = 1;
            else fac[i] = fac[i - 1] * i;
        }
        finv.resize(n + 1);
        finv[n] = fac[n].inverse();
        for (int64_t i = n - 1; i >= m; --i) finv[i] = finv[i + 1] * (i + 1);
    }

    mint fact(int64_t x) {
        assert(x >= 0 && x < fac.size());
        return fac[x];
    }

    mint combi(int64_t n, int64_t k) {
        if (n < k || n < 0 || k < 0) return 0;
        _init(n);
        return fac[n] * finv[k] * finv[n - k];
    }

    mint combi_naive(int64_t n, int64_t k) {
        if (n - k < k) n = n - k;
        if (n < k || n < 0 || k < 0) return 0;
        mint res = 1;
        for (int64_t i = 0; i < k; ++i) {
            res *= n - i;
            res /= i + 1;
        }
        return res;
    }

    mint permu(int64_t n, int64_t k) {
        if (n < k || n < 0 || k < 0) return 0;
        _init(n);
        return fac[n] * finv[n - k];
    }
};
math_mod<MOD> math;
