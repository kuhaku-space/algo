#include "_base.hpp"
#include "algo/modint.hpp"

template <int mod>
struct Combination {
    using mint = ModInt<mod>;
    vector<mint> fac, finv;

    Combination() {}

    mint operator()(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        _init(n);
        return fac[n] * finv[k] * finv[n - k];
    }

    void _init(int n) {
        if (fac.size() > n) return;
        int m = fac.size();
        fac.resize(n + 1);
        for (int i = m; i <= n; ++i) {
            if (i == 0)
                fac[i] = 1;
            else
                fac[i] = fac[i - 1] * i;
        }
        finv.resize(n + 1);
        finv[n] = fac[n].inverse();
        for (int i = n - 1; i >= m; --i) finv[i] = finv[i + 1] * (i + 1);
    }

    mint fact(int x) {
        assert(x >= 0);
        _init(x);
        return fac[x];
    }

    mint naive(int n, int k) const {
        if (n < k || n < 0 || k < 0) return 0;
        if (n - k < k) k = n - k;
        mint res = 1;
        for (int i = 0; i < k; ++i) {
            res *= n - i;
            res /= i + 1;
        }
        return res;
    }

    mint lucas(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        if (n - k < k) k = n - k;
        static vector<vector<mint>> v;
        if (v.empty()) {
            v = vector<vector<mint>>(mod, vector<mint>(mod));
            for (int i = 0; i < mod; ++i) v[i][0] = 1;
            for (int i = 0; i < mod; ++i) {
                for (int j = 1; j < mod; ++j) {
                    if (i < j)
                        v[i][j] = 0;
                    else if (i - j < j)
                        v[i][j] = v[i][i - j];
                    else
                        v[i][j] = v[i][j - 1] * mint(i + 1 - j) / mint(j);
                }
            }
        }
        mint res = 1;
        while (n || k) {
            res *= v[n % mod][k % mod];
            n /= mod, k /= mod;
        }
        return res;
    }

    mint permu(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        _init(n);
        return fac[n] * finv[n - k];
    }
};
Combination<MOD> combi;
