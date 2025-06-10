#pragma once
#include <algorithm>
#include <vector>
#include "graph/graph.hpp"

/// @brief LowLink
template <class T>
struct low_link {
    low_link(const Graph<T> &_g) : low_link(_g, _g.size()) {}

    /// @brief Get the articulation points object
    auto get_articulation_points() { return articulation_points; }
    /// @brief Get the bridges object
    auto get_bridges() { return bridges; }

  private:
    const Graph<T> &g;
    std::vector<int> ord, low;
    std::vector<bool> used;
    std::vector<int> articulation_points;               // 関節点
    std::vector<typename Graph<T>::edge_type> bridges;  // 橋

    low_link(const Graph<T> &_g, int n) : g(_g), ord(n), low(n), used(n) { build(); }

    void build() {
        int number = 0;
        for (int i = 0; i < g.size(); i++) {
            if (!used[i]) number = dfs(i, number, -1);
        }
    }

    int dfs(int index, int number, int parent) {
        used[index] = true;
        ord[index] = number++;
        low[index] = ord[index];
        bool is_articulation_point = false;
        int count = 0;
        for (auto &e : g[index]) {
            if (!used[e.to()]) {
                ++count;
                number = dfs(e.to(), number, index);
                low[index] = std::min(low[index], low[e.to()]);
                is_articulation_point |= ~parent && low[e.to()] >= ord[index];
                if (ord[index] < low[e.to()]) bridges.emplace_back(e);
            } else if (e.to() != parent) {
                low[index] = std::min(low[index], ord[e.to()]);
            }
        }
        is_articulation_point |= parent == -1 && count > 1;
        if (is_articulation_point) articulation_points.emplace_back(index);
        return number;
    }
};
