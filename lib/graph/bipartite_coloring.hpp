#pragma once
#include <optional>
#include <vector>
#include "graph/graph.hpp"

/// @brief 二部グラフ判定と 2 彩色
/// @details 2 彩色は連結成分ごとに色の入れ替えを除いて一意なので、
///          各成分で大きい側を色 0 に選ぶことで色 0 の頂点数を全体で最大化する
///          （同数なら成分の代表頂点側を色 0 とする）。
///          色 1 を最大化したい場合は全頂点の色を反転すればよい。
/// @tparam G グラフ型（無向グラフを想定、`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @return 二部グラフなら各頂点の色（0/1）の割り当て、そうでなければ `std::nullopt`
template <graph_type G>
std::optional<std::vector<int>> bipartite_coloring(const G &g) {
    int n = g.size();
    std::vector<int> color(n, -1);
    // 反復 DFS（再帰だと深いグラフでスタックオーバーフローしうる）
    std::vector<int> st, comp;
    for (int i = 0; i < n; ++i) {
        if (color[i] != -1) continue;
        color[i] = 0;
        st.emplace_back(i);
        comp.clear();
        int cnt0 = 0;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            comp.emplace_back(v);
            cnt0 += color[v] == 0;
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
        if (cnt0 * 2 < (int)comp.size()) {
            for (int v : comp) color[v] ^= 1;
        }
    }
    return color;
}
