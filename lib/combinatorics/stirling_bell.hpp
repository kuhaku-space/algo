#pragma once
#include <vector>
#include "combinatorics/combination.hpp"
#include "math/modint.hpp"

/// @brief 第2種スターリング数・ベル数
template <internal::modint mint = modint998>
struct StirlingBell {
    StirlingBell() : _binom(), _data() {}

    // 第2種スターリング数 S(n,k): O(k log n)
    mint stirling(int n, int k) {
        mint res = 0;
        for (int i = 0; i < k; ++i) {
            if (i & 1) res -= _binom.binom(k, k - i) * mint(k - i).pow(n);
            else res += _binom.binom(k, k - i) * mint(k - i).pow(n);
        }
        res *= _binom.finv(k);
        return res;
    }

    // sum_{j=0}^{k} S(n,j)（k=n で通常のベル数 B(n)）: 初回呼び出しは _init の O(k) 償却込みで O(k log n)
    mint bell(int n, int k) {
        _init(k);
        mint res = 0;
        for (int i = 0; i <= k; ++i) res += mint(i).pow(n) * _binom.finv(i) * _data[k - i];
        return res;
    }

  private:
    Combinatorics<mint> _binom;
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
