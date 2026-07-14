#pragma once
#include <optional>
#include <vector>
#include "graph/graph.hpp"

/// @brief 二部グラフ判定と 2 彩色
/// @tparam G グラフ型（無向グラフを想定、`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @return 二部グラフなら各頂点の色（0/1）の割り当て、そうでなければ `std::nullopt`
template <graph_type G>
std::optional<std::vector<int>> bipartite_coloring(const G &g) {
    int n = g.size();
    std::vector<int> color(n, -1);
    // 反復 DFS（再帰だと深いグラフでスタックオーバーフローしうる）
    std::vector<int> st;
    for (int i = 0; i < n; ++i) {
        if (color[i] != -1) continue;
        color[i] = 0;
        st.emplace_back(i);
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            for (auto &e : g[v]) {
                int u = e.to();
                if (color[u] == -1) {
                    color[u] = color[v] ^ 1;
                    st.emplace_back(u);
                } else if (color[u] == color[v]) {
                    return std::nullopt;
                }
            }
        }
    }
    return color;
}
