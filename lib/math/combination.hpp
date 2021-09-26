#include "algo/modint.hpp"
#include "template/template.hpp"

template <int mod>
struct Combination {
    using mint = ModInt<mod>;
    vector<mint> _fact, _finv;

    Combination() : _fact(), _finv() {}

    mint operator()(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        _init(n);
        return _fact[n] * _finv[k] * _finv[n - k];
    }

    void _init(int n) {
        if (_fact.size() > n) return;
        int m = _fact.size();
        _fact.resize(n + 1);
        for (int i = m; i <= n; ++i) {
            if (i == 0)
                _fact[i] = 1;
            else
                _fact[i] = _fact[i - 1] * i;
        }
        _finv.resize(n + 1);
        _finv[n] = _fact[n].inverse();
        for (int i = n - 1; i >= m; --i) _finv[i] = _finv[i + 1] * (i + 1);
    }

    mint fact(int x) {
        assert(x >= 0);
        _init(x);
        return _fact[x];
    }

    mint finv(int x) {
        assert(x >= 0);
        _init(x);
        return _finv[x];
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
        return _fact[n] * _finv[n - k];
    }
};
Combination<MOD> combi;
