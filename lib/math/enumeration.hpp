#include "algo/modint.hpp"
#include "math/combination.hpp"
#include "template/template.hpp"

template <int mod>
struct Enumeration {
    using mint = ModInt<mod>;
    Combination<mod> combi;
    vector<mint> data;

    Enumeration() : combi(), data() {}

    void _init(int n) {
        if (data.size() > n) return;
        int m = data.size();
        data.resize(n + 1);
        for (int i = m; i <= n; ++i) {
            if (i == 0)
                data[i] = 1;
            else if (i & 1)
                data[i] = data[i - 1] - combi.finv(i);
            else
                data[i] = data[i - 1] + combi.finv(i);
        }
    }

    mint stirling(int n, int k) {
        mint res = 0;
        for (int i = 0; i < k; ++i) {
            if (i & 1)
                res -= combi(k, k - i) * mint(k - i).pow(n);
            else
                res += combi(k, k - i) * mint(k - i).pow(n);
        }
        res /= combi.fact(k);
        return res;
    }

    mint bell(int n, int k) {
        _init(k);
        mint res = 0;
        for (int i = 0; i <= k; ++i) {
            res += mint(i).pow(n) * combi.finv(i) * data[k - i];
        }
        return res;
    }
};
Enumeration<MOD> enume;
