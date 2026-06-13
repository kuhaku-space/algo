#pragma once
#include <queue>
#include <vector>
#include "graph/graph.hpp"

/// @brief 全域木（入力辺の重みを保ったまま無向 list_graph として返す）
/// @tparam G 重み付きグラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
template <weighted_graph_type G>
list_graph<graph_weight_t<G>> spanning_tree(const G &g, int r = 0) {
    int n = g.size();
    list_graph<graph_weight_t<G>> res(n);
    std::queue<int> que;
    std::vector<bool> visited(n);
    que.emplace(r);
    visited[r] = true;
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (auto &e : g[x]) {
            if (!visited[e.to()]) {
                res.add_edges(e.from(), e.to(), e.weight());
                que.emplace(e.to());
                visited[e.to()] = true;
            }
        }
    }
    return res;
}
