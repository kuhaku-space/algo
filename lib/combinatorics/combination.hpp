#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <vector>
#include "math/modint.hpp"

/// @brief 二項係数・階乗・順列
template <internal::modint mint = modint998>
struct Combinatorics {
    Combinatorics() : _fact(), _inv(), _finv() {}

    // n が _table_limit を超える場合はテーブルを持たず naive() に委譲する
    mint operator()(std::int64_t n, std::int64_t k) {
        if (n < k || n < 0 || k < 0) return 0;
        if (n <= _table_limit) {
            _init((int)n);
            return _fact[n] * _finv[k] * _finv[n - k];
        }
        return naive(n, std::min(k, n - k));
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

    mint naive(std::int64_t n, std::int64_t k) const {
        if (n < k || n < 0 || k < 0) return 0;
        if (n - k < k) k = n - k;
        mint res = 1;
        for (std::int64_t i = 0; i < k; ++i) {
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
    // テーブルを確保する n の上限（超えると naive() にフォールバック）
    static constexpr std::int64_t _table_limit = 20'000'000;
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
