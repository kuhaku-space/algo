#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

/// @brief Mo's algorithm (rollback)
/// @see https://ei1333.hateblo.jp/entry/2017/09/11/211011
/// @see https://snuke.hatenablog.com/entry/2016/07/01/000000
struct RollbackMo {
    /// @brief 長さnの列に対するrollback Moを構築する
    /// @complexity $O(1)$
    RollbackMo(int _n) : query_left(), query_right(), order(), n(_n) {}

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

    /// @brief 左右共通の追加処理とロールバックで全クエリを実行する
    /// @complexity クエリ数を $q$ として、整列は $O(q\log q)$、
    /// コールバック呼び出しは $O((n+q)\sqrt q)$ 回
    template <class F, class G, class H, class I>
    void solve(F add, G save, H load, I answer) {
        return solve(add, add, save, load, answer);
    }
    /// @brief 左右別の追加処理とロールバックで全クエリを実行する
    /// @complexity クエリ数を $q$ として、整列は $O(q\log q)$、
    /// コールバック呼び出しは $O((n+q)\sqrt q)$ 回
    template <class F, class G, class H, class I, class J>
    void solve(F add_left, G add_right, H save, I load, J answer) {
        int q = query_left.size();
        int width = std::max(1, int(n / std::sqrt(q)));
        order.resize(q);
        std::iota(order.begin(), order.end(), 0);
        std::sort(order.begin(), order.end(), [&](int a, int b) -> bool {
            if (query_left[a] / width != query_left[b] / width) return query_left[a] < query_left[b];
            return query_right[a] < query_right[b];
        });

        auto initial = save();
        for (auto &&idx : order) {
            if (query_right[idx] - query_left[idx] < width) {
                for (int i = query_left[idx]; i < query_right[idx]; i++) add_right(i);
                answer(idx);
                load(initial);
            }
        }

        int cur_right = 0, last_block = -1;
        for (auto idx : order) {
            if (query_right[idx] - query_left[idx] < width) continue;
            int block = query_left[idx] / width;
            if (block != last_block) {
                load(initial);
                last_block = block;
                cur_right = (block + 1) * width;
            }
            while (cur_right < query_right[idx]) add_right(cur_right++);
            auto snapshot = save();
            for (int j = (block + 1) * width - 1; j >= query_left[idx]; --j) add_left(j);
            answer(idx);
            load(snapshot);
        }
    }

  private:
    std::vector<int> query_left, query_right, order;
    int n;
};
