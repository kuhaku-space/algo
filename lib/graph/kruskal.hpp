#pragma once
#include <algorithm>
#include <vector>
#include "data_structure/union_find.hpp"
#include "graph/graph.hpp"

/// @brief クラスカル法
/// @tparam G 重み付きグラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
template <weighted_graph_type G>
std::vector<graph_edge_t<G>> kruskal(const G &g) {
    using _edge = graph_edge_t<G>;
    union_find uf(g.size());
    std::vector<_edge> res;
    std::vector<_edge> edge_list;
    edge_list.reserve(g.edge_count());
    for (auto &e : g.all_edges()) edge_list.emplace_back(e);
    std::sort(edge_list.begin(), edge_list.end());
    for (auto &e : edge_list) {
        if (uf.unite(e.from(), e.to())) res.emplace_back(e);
    }
    return res;
}
