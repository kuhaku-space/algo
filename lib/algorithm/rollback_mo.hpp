#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

/// @brief Mo's algorithm (rollback)
/// @see https://ei1333.hateblo.jp/entry/2017/09/11/211011
/// @see https://snuke.hatenablog.com/entry/2016/07/01/000000
struct rollback_mo {
    /// @brief 長さnの列に対するrollback Moを構築する
    /// @complexity $O(1)$
    rollback_mo(int n) : _left(), _right(), _order(), _size(n) {}

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

    /// @brief 左右共通の追加処理とロールバックで全クエリを実行する
    /// @complexity クエリ数を $q$ として、整列は $O(q\log q)$、
    /// コールバック呼び出しは $O((n+q)\sqrt q)$ 回
    template <class F, class G, class H, class I>
    void solve(F rem, G save, H load, I add) {
        return solve(rem, save, load, add, add);
    }
    /// @brief 左右別の追加処理とロールバックで全クエリを実行する
    /// @complexity クエリ数を $q$ として、整列は $O(q\log q)$、
    /// コールバック呼び出しは $O((n+q)\sqrt q)$ 回
    template <class F, class G, class H, class I, class J>
    void solve(F rem, G save, H load, I addl, J addr) {
        int q = _left.size();
        int width = std::max(1, int(_size / std::sqrt(q)));
        _order.resize(q);
        std::iota(_order.begin(), _order.end(), 0);
        std::sort(_order.begin(), _order.end(), [&](int a, int b) -> bool {
            if (_left[a] / width != _left[b] / width) return _left[a] < _left[b];
            return _right[a] < _right[b];
        });

        auto reset = save();
        for (auto &&idx : _order) {
            if (_right[idx] - _left[idx] < width) {
                for (int i = _left[idx]; i < _right[idx]; i++) addr(i);
                rem(idx);
                load(reset);
            }
        }

        int right = 0, last_block = -1;
        for (auto idx : _order) {
            if (_right[idx] - _left[idx] < width) continue;
            int block = _left[idx] / width;
            if (block != last_block) {
                load(reset);
                last_block = block;
                right = (block + 1) * width;
            }
            while (right < _right[idx]) addr(right++);
            auto snapshot = save();
            for (int j = (block + 1) * width - 1; j >= _left[idx]; --j) addl(j);
            rem(idx);
            load(snapshot);
        }
    }

  private:
    std::vector<int> _left, _right, _order;
    int _size;
};
