#pragma once
#include <functional>
#include <queue>
#include <vector>
#include "graph/graph.hpp"

/// @brief プリム法
/// @tparam G 重み付きグラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @complexity $O(E\log E)$
template <weighted_graph_type G>
std::vector<graph_edge_t<G>> prim(const G &g, int r = 0) {
    using _edge = graph_edge_t<G>;
    std::vector<_edge> res;
    std::vector<bool> visited(g.size());
    visited[r] = true;
    std::priority_queue<_edge, std::vector<_edge>, std::greater<>> p_que;
    for (auto &e : g[r]) p_que.emplace(e);
    while (!p_que.empty()) {
        auto edge = p_que.top();
        p_que.pop();
        if (visited[edge.to()]) continue;
        visited[edge.to()] = true;
        res.emplace_back(edge);
        for (auto &e : g[edge.to()]) {
            if (!visited[e.to()]) p_que.emplace(e);
        }
    }
    return res;
}
