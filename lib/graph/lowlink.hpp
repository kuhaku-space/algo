#pragma once
#include <algorithm>
#include <vector>
#include "graph/graph.hpp"

/// @brief LowLink
template <class T>
struct low_link {
    low_link(const Graph<T> &_g) : low_link(_g, _g.size()) {}

    /// @brief 関節点（頂点番号）の一覧を取得する
    const std::vector<int> &get_articulation_points() const { return articulation_points; }
    /// @brief 橋の一覧を辺 ID で取得する（頂点は g.get_edge(id) で引ける）
    const std::vector<int> &get_bridges() const { return bridges; }

  private:
    const Graph<T> &g;
    std::vector<int> ord, low;
    std::vector<bool> used;
    std::vector<int> articulation_points;  // 関節点（頂点番号）
    std::vector<int> bridges;              // 橋（辺 ID）

    low_link(const Graph<T> &_g, int n) : g(_g), ord(n), low(n), used(n) { build(); }

    void build() {
        int number = 0;
        for (int i = 0; i < g.size(); i++) {
            if (!used[i]) number = dfs(i, number, -1);
        }
    }

    /// @param parent_edge_id index に入ってきた辺の ID（根は -1）。
    ///        親へ戻る辺は「同じ ID の辺」で除外する。多重辺は ID が異なるため
    ///        back edge として正しく扱われ、橋・関節点の誤判定を防ぐ。
    int dfs(int index, int number, int parent_edge_id) {
        used[index] = true;
        ord[index] = number++;
        low[index] = ord[index];
        bool is_articulation_point = false;
        int count = 0;
        for (auto &e : g[index]) {
            if (e.id() == parent_edge_id) continue;  // 親へ来た辺そのものは無視
            if (!used[e.to()]) {
                ++count;
                number = dfs(e.to(), number, e.id());
                low[index] = std::min(low[index], low[e.to()]);
                is_articulation_point |= parent_edge_id != -1 && low[e.to()] >= ord[index];
                if (ord[index] < low[e.to()]) bridges.emplace_back(e.id());
            } else {
                low[index] = std::min(low[index], ord[e.to()]);
            }
        }
        is_articulation_point |= parent_edge_id == -1 && count > 1;
        if (is_articulation_point) articulation_points.emplace_back(index);
        return number;
    }
};
