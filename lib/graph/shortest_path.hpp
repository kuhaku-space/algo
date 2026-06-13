#pragma once
#include <functional>
#include <limits>
#include <queue>
#include <vector>
#include "graph/graph.hpp"

/// @brief 単一始点最短路（実重み付きグラフはダイクストラ法）
/// @tparam G 実重み付きグラフ型（`list_graph<T>` / `csr_graph<T>`、T は非 void）
/// @note 重みなしグラフ（`*_graph<void>`）は下の BFS 版が選ばれる。
template <properly_weighted_graph_type G, class T = graph_weight_t<G>>
std::vector<T> shortest_path(const G &g, int s = 0, T inf = std::numeric_limits<T>::max()) {
    struct _node {
        constexpr _node() : _to(), _dist() {}
        constexpr _node(int to, T dist) : _to(to), _dist(dist) {}
        constexpr bool operator<(const _node &rhs) const { return this->dist() < rhs.dist(); }
        constexpr bool operator>(const _node &rhs) const { return rhs < *this; }

        constexpr int to() const { return this->_to; }
        constexpr T dist() const { return this->_dist; }

      private:
        int _to;
        T _dist;
    };
    std::vector<T> dists(g.size(), inf);
    std::priority_queue<_node, std::vector<_node>, std::greater<>> p_que;
    dists[s] = T();
    p_que.emplace(s, T());
    while (!p_que.empty()) {
        auto node = p_que.top();
        p_que.pop();
        if (dists[node.to()] < node.dist()) continue;
        for (auto &e : g[node.to()]) {
            if (node.dist() + e.weight() < dists[e.to()]) {
                dists[e.to()] = node.dist() + e.weight();
                p_que.emplace(e.to(), dists[e.to()]);
            }
        }
    }
    return dists;
}

/// @brief 単一始点最短路（重みなしグラフは BFS で O(V+E)）
/// @tparam G 重みなしグラフ型（`list_graph<void>` / `csr_graph<void>` のいずれでも可）
/// @note 重みが 1 固定なので priority_queue 不要。`unweighted_graph_type` と
///       `properly_weighted_graph_type` は排他なので、重みなしグラフではこちらが選ばれる。
template <unweighted_graph_type G>
std::vector<int> shortest_path(const G &g, int s = 0, int inf = std::numeric_limits<int>::max()) {
    std::vector<int> dists(g.size(), inf);
    std::queue<int> que;
    dists[s] = 0;
    que.emplace(s);
    while (!que.empty()) {
        auto index = que.front();
        que.pop();
        for (auto &e : g[index]) {
            if (dists[index] + 1 < dists[e.to()]) {
                dists[e.to()] = dists[index] + 1;
                que.emplace(e.to());
            }
        }
    }
    return dists;
}
