#pragma once
#include <vector>
#include "math/combination.hpp"
#include "math/modint.hpp"

template <class mint = modint998, internal::is_modint_t<mint> * = nullptr>
struct Enumeration {
    Enumeration() : _binom(), _data() {}

    mint stirling(int n, int k) {
        mint res = 0;
        for (int i = 0; i < k; ++i) {
            if (i & 1) res -= _binom(k, k - i) * mint(k - i).pow(n);
            else res += _binom(k, k - i) * mint(k - i).pow(n);
        }
        res *= _binom.finv(k);
        return res;
    }

    mint bell(int n, int k) {
        _init(k);
        mint res = 0;
        for (int i = 0; i <= k; ++i) res += mint(i).pow(n) * _binom.finv(i) * _data[k - i];
        return res;
    }

  private:
    Combination<mint> _binom;
    std::vector<mint> _data;

    void _init(int n) {
        if ((int)_data.size() > n) return;
        int m = _data.size();
        _data.resize(n + 1);
        for (int i = m; i <= n; ++i) {
            if (i == 0) _data[i] = 1;
            else if (i & 1) _data[i] = _data[i - 1] - _binom.finv(i);
            else _data[i] = _data[i - 1] + _binom.finv(i);
        }
    }
};
