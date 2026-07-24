#pragma once
#include <utility>
#include <vector>
#include "graph/graph.hpp"

/// @brief 根付き木を部分木区間へ写すオイラーツアー
/// @complexity 構築は $O(n)$、各アクセサと区間取得は $O(1)$
struct euler_tour {
    /// @brief グラフ `g` を頂点 `r` を根とするオイラーツアーへ変換する
    /// @param g 木を表すグラフ
    /// @param r 根
    /// @complexity $O(n)$
    template <graph_type G>
    euler_tour(const G &g, int r = 0) : euler_tour(g, g.size(), r) {}

    /// @brief 頂点 `i` の部分木に対応する半開区間 `[left, right)` を返す
    /// @complexity $O(1)$
    std::pair<int, int> operator[](int i) const { return std::make_pair(ls[i], rs[i]); }

    /// @brief 頂点数を返す
    /// @complexity $O(1)$
    int size() const { return _size; }

    /// @brief 頂点 `i` の部分木区間の左端を返す
    /// @complexity $O(1)$
    int left(int i) const { return ls[i]; }
    /// @brief 頂点 `i` の部分木区間の右端を返す
    /// @complexity $O(1)$
    int right(int i) const { return rs[i]; }
    /// @brief 頂点 `i` の行きがけ順を返す
    /// @complexity $O(1)$
    int order(int i) const { return ord[i]; }

    /// @brief 頂点 `v` の部分木区間 `[l, r)` を `f(l, r)` に渡す
    /// @complexity $O(1)$（`f` の実行時間を除く）
    template <class F>
    void query(int v, const F &f) const {
        f(ls[v], rs[v]);
    }

  private:
    int _size;
    std::vector<int> ord, ls, rs;

    template <class G>
    euler_tour(const G &g, int n, int r) : _size(n), ord(n), ls(n, -1), rs(n) {
        int c = 0;
        std::vector<int> stk;
        stk.reserve(2 * n);
        stk.emplace_back(r);
        while (!stk.empty()) {
            auto x = stk.back();
            stk.pop_back();
            if (x < 0) {
                rs[~x] = c;
                continue;
            }
            ls[x] = c;
            ord[x] = c++;
            rs[x] = c;
            for (auto &e : g[x]) {
                int to = e.to();
                if (ls[to] != -1) continue;
                stk.emplace_back(~x);
                stk.emplace_back(to);
            }
        }
    }
};
