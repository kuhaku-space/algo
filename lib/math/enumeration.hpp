#pragma once
#include <vector>
#include "math/combination.hpp"
#include "math/modint.hpp"

template <class mint = modint998, internal::is_modint_t<mint> * = nullptr>
struct Enumeration {
    Enumeration() : combi(), data() {}

    mint stirling(int n, int k) {
        mint res = 0;
        for (int i = 0; i < k; ++i) {
            if (i & 1) res -= combi(k, k - i) * mint(k - i).pow(n);
            else res += combi(k, k - i) * mint(k - i).pow(n);
        }
        res *= combi.finv(k);
        return res;
    }

    mint bell(int n, int k) {
        _init(k);
        mint res = 0;
        for (int i = 0; i <= k; ++i) res += mint(i).pow(n) * combi.finv(i) * data[k - i];
        return res;
    }

  private:
    Combination<mint> combi;
    std::vector<mint> data;

    void _init(int n) {
        if ((int)data.size() > n) return;
        int m = data.size();
        data.resize(n + 1);
        for (int i = m; i <= n; ++i) {
            if (i == 0) data[i] = 1;
            else if (i & 1) data[i] = data[i - 1] - combi.finv(i);
            else data[i] = data[i - 1] + combi.finv(i);
        }
    }
};
