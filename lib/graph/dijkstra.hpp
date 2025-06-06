#pragma once
#include <functional>
#include <limits>
#include <queue>
#include <vector>
#include "graph/graph.hpp"

/// @brief ダイクストラ法
template <class T>
std::vector<T> dijkstra(const Graph<T> &g, int s = 0, T inf = std::numeric_limits<T>::max()) {
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

/// @brief ダイクストラ法
std::vector<int> dijkstra(const Graph<void> &g, int s = 0, int inf = std::numeric_limits<int>::max()) {
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
