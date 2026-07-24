#pragma once
#include <vector>
#include "combinatorics/combination.hpp"
#include "math/modint.hpp"

/// @brief 第2種スターリング数・ベル数
/// @details 二項係数と累乗を使い、1要素または部分和をオンデマンドに求める。
/// @tparam mint 法が素数の modint 型
template <internal::modint mint = modint998>
struct StirlingBell {
    /// @brief 空の計算テーブルを構築する
    /// @complexity $O(1)$
    StirlingBell() : _binom(), _data() {}

    /// @brief 第2種スターリング数 $S(n,k)$ を返す
    /// @param n 行番号。1以上であること
    /// @param k 列番号。$1\le k\le n$ であること
    /// @complexity $O(k\log n)$
    mint stirling(int n, int k) {
        mint res = 0;
        for (int i = 0; i < k; ++i) {
            if (i & 1) res -= _binom.binom(k, k - i) * mint(k - i).pow(n);
            else res += _binom.binom(k, k - i) * mint(k - i).pow(n);
        }
        res *= _binom.finv(k);
        return res;
    }

    /// @brief 第2種スターリング数の部分和 $\sum_{j=0}^{k}S(n,j)$ を返す
    /// @details $k=n$ のとき通常のベル数 $B_n$ になる。
    /// @param n 行番号。0以上であること
    /// @param k 和を取る最大の列番号。0以上であること
    /// @complexity $O(k\log n)$。未構築部分の前計算 $O(k)$ を含む
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
