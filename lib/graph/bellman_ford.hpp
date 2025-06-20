#pragma once
#include <limits>
#include <vector>
#include "graph/graph.hpp"

/// @brief ベルマンフォード法
template <class T>
std::vector<T> bellman_ford(const Graph<T> &graph, int s = 0, T inf = std::numeric_limits<T>::max(),
                            T ninf = std::numeric_limits<T>::lowest()) {
    int n = graph.size();
    std::vector<T> dists(n, inf);
    dists[s] = T();
    bool updated = true;
    for (int count = 0; updated && count <= n << 1; ++count) {
        updated = false;
        for (int i = 0; i < n; ++i) {
            if (dists[i] == inf) continue;
            for (auto &e : graph[i]) {
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
