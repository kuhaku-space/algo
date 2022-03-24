#pragma once
#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief トポロジカルソート
 *
 * @tparam T 辺の重みの型
 * @param g グラフ
 * @return std::vector<int> 頂点の順序
 */
template <class T>
std::vector<int> topological_sort(const Graph<T> &g) {
    int n = g.size();
    std::vector<int> res;
    std::vector<bool> seen(n);
    auto dfs = [&](auto self, int v) {
        if (seen[v]) return;
        seen[v] = true;
        for (auto &e : g[v])
            if (!seen[e.to()]) self(self, e.to());
        res.emplace_back(v);
    };
    for (int i = 0; i < n; ++i) dfs(dfs, i);
    std::reverse(res.begin(), res.end());
    return res;
}
