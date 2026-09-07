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
    Mo(int _n) : query_left(), query_right(), order(), n(_n), cur_left(0), cur_right(0) {}

    /// @brief 標準入力からq個の区間を追加する
    /// @param q 読み込む区間の個数
    /// @param origin 入力の添字の起点（1-indexedなら1、0-indexedなら0）
    /// @param closed 入力が閉区間 $[l, r]$ ならtrue、半開区間 $[l, r)$ ならfalse
    /// @complexity $O(q)$
    void input(int q, int origin = 1, bool closed = false) {
        for (int i = 0; i < q; ++i) {
            int l, r;
            std::cin >> l >> r;
            add(l - origin, r - origin + closed);
        }
    }

    /// @brief 半開区間を追加する
    /// @complexity 償却 $O(1)$
    void add(int l, int r) {
        query_left.emplace_back(l);
        query_right.emplace_back(r);
    }

    /// @brief 左右共通の追加・削除処理で全クエリを実行する
    /// @complexity クエリ数を $q$ として、整列は $O(q\log q)$、
    /// コールバック呼び出しは $O((n+q)\sqrt q)$ 回
    template <class F, class G, class H>
    void solve(F add, G del, H answer) {
        return solve(add, add, del, del, answer);
    }

    /// @brief 左右別の追加・削除処理で全クエリを実行する
    /// @complexity クエリ数を $q$ として、整列は $O(q\log q)$、
    /// コールバック呼び出しは $O((n+q)\sqrt q)$ 回
    template <class F, class G, class H, class I, class J>
    void solve(F add_left, G add_right, H del_left, I del_right, J answer) {
        build();
        for (int idx : order) {
            while (cur_left > query_left[idx]) add_left(--cur_left);
            while (cur_right < query_right[idx]) add_right(cur_right++);
            while (cur_left < query_left[idx]) del_left(cur_left++);
            while (cur_right > query_right[idx]) del_right(--cur_right);
            answer(idx);
        }
    }

  private:
    std::vector<int> query_left, query_right, order;
    int n, cur_left, cur_right;

    void build() {
        int q = query_left.size();
        int width = std::max(1, int(n / std::sqrt(q)));
        order.resize(q);
        std::iota(order.begin(), order.end(), 0);
        std::sort(order.begin(), order.end(), [&](int a, int b) -> bool {
            if (query_left[a] / width != query_left[b] / width) return query_left[a] < query_left[b];
            return (query_left[a] / width % 2 == 0) ? (query_right[a] < query_right[b])
                                                    : (query_right[b] < query_right[a]);
        });
    }
};
