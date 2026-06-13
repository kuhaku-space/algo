#pragma once
#include <algorithm>
#include <utility>
#include <vector>
#include "graph/graph.hpp"

/// @brief トポロジカルソート
template <class T>
std::vector<int> topological_sort(const Graph<T> &g) {
    int n = g.size();
    std::vector<int> res;
    std::vector<bool> seen(n);
    // 反復 DFS（再帰だと深いグラフでスタックオーバーフローしうる）。
    // 子を処理し終えた後に res へ push する帰りがけ順を再現し、最後に反転する。
    std::vector<std::pair<int, int>> stk;
    stk.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (seen[i]) continue;
        seen[i] = true;
        stk.emplace_back(i, 0);
        while (!stk.empty()) {
            auto &[v, idx] = stk.back();
            if (idx < (int)g[v].size()) {
                int to = g[v][idx++].to();
                if (!seen[to]) {
                    seen[to] = true;
                    stk.emplace_back(to, 0);
                }
            } else {
                res.emplace_back(v);
                stk.pop_back();
            }
        }
    }
    std::reverse(res.begin(), res.end());
    return res;
}
