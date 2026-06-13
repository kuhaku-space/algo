#pragma once
#include <limits>
#include <vector>
#include "graph/graph.hpp"

/// @brief ベルマンフォード法
/// @tparam G 重み付きグラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
template <weighted_graph_type G, class T = graph_weight_t<G>>
std::vector<T> bellman_ford(const G &g, int s = 0, T inf = std::numeric_limits<T>::max(),
                            T ninf = std::numeric_limits<T>::lowest()) {
    int n = g.size();
    std::vector<T> dists(n, inf);
    dists[s] = T();
    bool updated = true;
    for (int count = 0; updated && count <= n << 1; ++count) {
        updated = false;
        for (int i = 0; i < n; ++i) {
            if (dists[i] == inf) continue;
            for (auto &e : g[i]) {
                if (dists[i] == ninf || dists[i] + e.weight() < dists[e.to()]) {
                    if (dists[e.to()] == ninf) continue;
                    updated = true;
                    if (count >= n) dists[e.to()] = ninf;
                    else dists[e.to()] = dists[i] + e.weight();
                }
            }
        }
    }
    return dists;
}
