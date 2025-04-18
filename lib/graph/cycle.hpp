#pragma once
#include <vector>
#include "graph/graph.hpp"

/// @brief 閉路検出
template <class T>
bool has_cycle(const Graph<T> &g) {
    int n = g.size();
    std::vector<bool> seen(n), finished(n);
    bool res = false;

    auto dfs = [&](auto self, int index) -> void {
        if (finished[index]) return;
        seen[index] = true;
        for (auto &e : g[index]) {
            if (res |= seen[e.to()]) return;
            self(self, e.to());
        }
        seen[index] = false;
        finished[index] = true;
    };

    for (int i = 0; i < n; ++i) {
        if (res) break;
        dfs(dfs, i);
    }
    return res;
}
