#pragma once
#include <utility>
#include <vector>
#include "graph/graph.hpp"

/// @brief 重心分解
template <class T>
std::vector<std::pair<int, int>> centroid_decomposition_with_edge(const Graph<T> &g) {
    int n = g.size();
    std::vector<std::pair<int, int>> par(n, {-1, -1});
    std::vector<int> size(n), size_par(n, -2);
    std::vector<bool> used(n, false);
    auto dfs = [&](auto self, int x, int p) -> int {
        if (size_par[x] == p) return size[x];
        int sum = 1;
        for (auto e : g[x]) {
            if (used[e.to()] || e.to() == p) continue;
            sum += self(self, e.to(), x);
        }
        size_par[x] = p;
        return size[x] = sum;
    };
    auto build = [&](auto self, int x, int p, int z) -> void {
        int sz = dfs(dfs, x, p);
        bool is_centroid = false;
        while (!is_centroid) {
            is_centroid = true;
            for (auto e : g[x]) {
                if (size[e.to()] > size[x] || size[e.to()] * 2 <= sz) continue;
                x = e.to();
                is_centroid = false;
                break;
            }
        }
        par[x] = {p, z};
        used[x] = true;
        for (auto e : g[x]) {
            if (used[e.to()]) continue;
            self(self, e.to(), x, e.to());
        }
    };

    build(build, 0, -1, -1);
    return par;
}

/// @brief 重心分解
template <class T>
std::vector<int> centroid_decomposition(const Graph<T> &g) {
    int n = g.size();
    std::vector<int> par(n);
    auto v = centroid_decomposition_with_edge(g);
    for (int i = 0; i < n; ++i) par[i] = v[i].first;
    return par;
}
