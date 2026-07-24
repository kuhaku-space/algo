#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

/// @brief Mo's algorithm
/// @see https://ei1333.hateblo.jp/entry/2017/09/11/211011
/// @see https://snuke.hatenablog.com/entry/2016/07/01/000000
struct Mo {
    /// @brief 長さnの列に対するMoを構築する
    /// @complexity $O(1)$
    Mo(int n) : _left(), _right(), _order(), _size(n), _nl(0), _nr(0) {}

    /// @brief 標準入力からq個の区間を追加する
    /// @complexity $O(q)$
    void input(int q, int bias = 1, int closed = 0) {
        for (int i = 0; i < q; ++i) {
            int l, r;
            std::cin >> l >> r;
            add(l - bias, r - bias + closed);
        }
    }

    /// @brief 半開区間を追加する
    /// @complexity 償却 $O(1)$
    void add(int l, int r) {
        _left.emplace_back(l);
        _right.emplace_back(r);
    }
    /// @brief addと同じ
    /// @complexity 償却 $O(1)$
    void emplace(int l, int r) { return add(l, r); }

    /// @brief addと同じ
    /// @complexity 償却 $O(1)$
    void insert(int l, int r) { return add(l, r); }

    /// @brief 左右共通の追加・削除処理で全クエリを実行する
    /// @complexity クエリ数を $q$ として、整列は $O(q\log q)$、
    /// コールバック呼び出しは $O((n+q)\sqrt q)$ 回
    template <class F, class G, class H>
    void solve(F add, G del, H rem) {
        build();
        for (int idx : _order) {
            while (_nl > _left[idx]) add(--_nl);
            while (_nr < _right[idx]) add(_nr++);
            while (_nl < _left[idx]) del(_nl++);
            while (_nr > _right[idx]) del(--_nr);
            rem(idx);
        }
    }

    /// @brief 左右別の追加・削除処理で全クエリを実行する
    /// @complexity クエリ数を $q$ として、整列は $O(q\log q)$、
    /// コールバック呼び出しは $O((n+q)\sqrt q)$ 回
    template <class F, class G, class H, class I, class K>
    void solve(F addl, G addr, H dell, I delr, K rem) {
        build();
        for (int idx : _order) {
            while (_nl > _left[idx]) addl(--_nl);
            while (_nr < _right[idx]) addr(_nr++);
            while (_nl < _left[idx]) dell(_nl++);
            while (_nr > _right[idx]) delr(--_nr);
            rem(idx);
        }
    }

  private:
    std::vector<int> _left, _right, _order;
    int _size, _nl, _nr;

    void build() {
        int q = _left.size();
        int width = std::max(1, int(_size / std::sqrt(q)));
        _order.resize(q);
        std::iota(_order.begin(), _order.end(), 0);
        std::sort(_order.begin(), _order.end(), [&](int a, int b) -> bool {
            if (_left[a] / width != _left[b] / width) return _left[a] < _left[b];
            return (_left[a] / width % 2 == 0) ? (_right[a] < _right[b]) : (_right[b] < _right[a]);
        });
    }
};
