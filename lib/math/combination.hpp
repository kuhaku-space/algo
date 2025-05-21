#pragma once
#include <cassert>
#include <concepts>
#include <vector>
#include "math/modint.hpp"

/// @brief 二項係数
template <class mint = modint998>
requires(std::derived_from<mint, internal::modint_base>)
struct Combination {
    Combination() : _fact(), _inv(), _finv() {}

    mint operator()(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        _init(n);
        return _fact[n] * _finv[k] * _finv[n - k];
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

    mint permu(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        _init(n);
        return _fact[n] * _finv[n - k];
    }

  private:
    static constexpr int _mod = mint::mod();
    std::vector<mint> _fact, _inv, _finv;

    void _init(int n) {
        if ((int)_fact.size() > n) return;
        int m = _fact.size();
        _fact.resize(n + 1);
        for (int i = m; i <= n; ++i) {
            if (i == 0) _fact[i] = 1;
            else _fact[i] = _fact[i - 1] * i;
        }
        _inv.resize(n + 1);
        for (int i = m; i <= n; ++i) {
            if (i <= 1) _inv[i] = 1;
            else _inv[i] = -_inv[_mod % i] * (_mod / i);
        }
        _finv.resize(n + 1);
        for (int i = m; i <= n; ++i) {
            if (i == 0) _finv[i] = 1;
            else _finv[i] = _finv[i - 1] * _inv[i];
        }
    }
};
