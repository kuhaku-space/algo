#pragma once
#include <vector>
#include "graph/graph.hpp"

/// @brief なもりグラフ上のサイクル検出
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
template <graph_type G>
std::vector<int> cycle_detection_on_namori_graph(const G &g) {
    int n = g.size();
    std::vector<int> cnt(n);
    std::vector<int> st;
    st.reserve(n);
    for (int i = 0; i < n; ++i) {
        cnt[i] = g[i].size();
        if (cnt[i] == 1) st.emplace_back(i);
    }
    while (!st.empty()) {
        int x = st.back();
        st.pop_back();
        for (auto &e : g[x]) {
            if ((--cnt[e.to()]) == 1) st.emplace_back(e.to());
        }
    }

    std::vector<int> parent(n, -2);
    st.clear();
    for (int i = 0; i < n; ++i) {
        if (cnt[i] >= 2) {
            parent[i] = -1;
            st.emplace_back(i);
        }
    }

    while (!st.empty()) {
        int x = st.back();
        st.pop_back();
        for (auto &e : g[x]) {
            if (parent[e.to()] == -2) {
                parent[e.to()] = x;
                st.emplace_back(e.to());
            }
        }
    }

    return parent;
}
