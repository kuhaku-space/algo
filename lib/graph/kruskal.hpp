#pragma once
#include <algorithm>
#include <vector>
#include "graph/graph.hpp"
#include "tree/union_find.hpp"

/// @brief クラスカル法
template <class T>
std::vector<typename Graph<T>::edge_type> kruskal(const Graph<T> &g) {
    using _edge = typename Graph<T>::edge_type;
    union_find uf(g.size());
    std::vector<_edge> res;
    std::vector<_edge> edge_list;
    for (auto &v : g) {
        for (auto &e : v) edge_list.emplace_back(e);
    }
    std::sort(edge_list.begin(), edge_list.end());
    for (auto &e : edge_list) {
        if (uf.unite(e.from(), e.to())) res.emplace_back(e);
    }
    return res;
}
