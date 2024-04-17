#pragma once
#include <queue>
#include <vector>
#include "graph/graph.hpp"

/**
 * @brief プリム法
 * @details 最小全域木を求める
 *
 * @tparam T 辺の重みの型
 * @param g グラフ
 * @param r 始点
 * @return std::vector<typename Graph<T>::edge_type>
 */
template <class T>
std::vector<typename Graph<T>::edge_type> prim(const Graph<T> &g, int r = 0) {
    using _edge = typename Graph<T>::edge_type;
    std::vector<_edge> res;
    std::vector<bool> visited(g.size());
    visited[r] = true;
    std::priority_queue<_edge, std::vector<_edge>, std::greater<>> p_que;
    for (auto &e : g[r]) p_que.emplace(e);
    while (!p_que.empty()) {
        auto edge = p_que.top();
        p_que.pop();
        if (visited[edge.to()]) continue;
        visited[edge.to()] = true;
        res.emplace_back(edge);
        for (auto &e : g[edge.to()]) {
            if (!visited[e.to()]) p_que.emplace(e);
        }
    }
    return res;
}
