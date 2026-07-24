#pragma once
#include <utility>
#include <vector>
#include "graph/graph.hpp"

/// @brief 根rからのBFS順を返す
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @complexity $O(V+E)$
template <graph_type G>
std::vector<int> tree_bfs(const G &g, int r = 0) {
    int pos = 0;
    std::vector<int> res;
    std::vector<bool> visited(g.size());
    res.emplace_back(r);
    visited[r] = true;
    while (pos < (int)res.size()) {
        auto index = res[pos++];
        for (auto &e : g[index]) {
            if (visited[e.to()]) continue;
            res.emplace_back(e.to());
            visited[e.to()] = true;
        }
    }
    return res;
}

/// @brief 親配列が表す木のBFS順を返す
/// @complexity $O(V)$
std::vector<int> tree_bfs(const std::vector<int> &parents) {
    int n = parents.size();
    list_graph<void> g(n);
    int r = 0;
    for (int i = 0; i < n; ++i) {
        if (parents[i] == -1 || parents[i] == i) {
            r = i;
            continue;
        }
        g.add_edges(i, parents[i]);
    }
    return tree_bfs(g, r);
}

/// @brief 根rからのDFS行きがけ順を返す
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @complexity $O(V+E)$
template <graph_type G>
std::vector<int> tree_dfs(const G &g, int r = 0) {
    std::vector<int> res;
    // 反復 DFS（再帰だと深い木でスタックオーバーフローしうる）。
    // 行きがけ順を保つため (頂点, 親) を積み、子は左から処理する。
    std::vector<std::pair<int, int>> stk;
    stk.reserve(g.size());
    stk.emplace_back(r, -1);
    while (!stk.empty()) {
        auto [index, parent] = stk.back();
        stk.pop_back();
        res.emplace_back(index);
        // 元の左→右の行きがけ順にするため逆順に積む
        for (auto it = g[index].rbegin(); it != g[index].rend(); ++it) {
            if (it->to() == parent) continue;
            stk.emplace_back(it->to(), index);
        }
    }
    return res;
}

/// @brief 木の距離を求める
/// @tparam G 重み付きグラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @complexity $O(V+E)$
template <weighted_graph_type G, class U = graph_weight_t<G>>
std::vector<U> tree_dist(const G &g, int r = 0) {
    std::vector<U> res(g.size(), -1);
    std::vector<int> stk;
    stk.reserve(g.size());
    res[r] = 0;
    stk.emplace_back(r);
    while (!stk.empty()) {
        auto index = stk.back();
        stk.pop_back();
        for (auto &e : g[index]) {
            if (res[e.to()] != -1) continue;
            res[e.to()] = res[index] + e.weight();
            stk.emplace_back(e.to());
        }
    }
    return res;
}

/// @brief 木の頂点の親を求める
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @complexity $O(V+E)$
template <graph_type G>
std::vector<int> tree_parent(const G &g, int r = 0) {
    std::vector<int> res(g.size(), -1);
    std::vector<int> stk;
    stk.reserve(g.size());
    res[r] = r;
    stk.emplace_back(r);
    while (!stk.empty()) {
        auto index = stk.back();
        stk.pop_back();
        for (auto &e : g[index]) {
            if (res[e.to()] != -1) continue;
            res[e.to()] = index;
            stk.emplace_back(e.to());
        }
    }
    res[r] = -1;
    return res;
}

/// @brief 部分木の大きさを求める
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @complexity $O(V+E)$
template <graph_type G>
std::vector<int> tree_subtree(const G &g, int r = 0) {
    std::vector<int> res(g.size());
    // 反復 DFS（再帰だと深い木でスタックオーバーフローしうる）。
    // 各フレームは (頂点, 親, 隣接走査位置)。隣接の再走査を避けるため位置を保持し、
    // 帰りがけに子の部分木サイズを親へ加算する。
    struct frame {
        int v, parent, idx;
    };
    std::vector<frame> stk;
    stk.reserve(g.size());
    stk.push_back({r, -1, 0});
    res[r] = 1;
    while (!stk.empty()) {
        frame &f = stk.back();
        if (f.idx < (int)g[f.v].size()) {
            int to = g[f.v][f.idx++].to();
            if (to == f.parent) continue;
            res[to] = 1;
            stk.push_back({to, f.v, 0});
        } else {
            int v = f.v, p = f.parent;
            stk.pop_back();
            if (p != -1) res[p] += res[v];
        }
    }
    return res;
}
