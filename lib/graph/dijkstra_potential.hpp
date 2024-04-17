#pragma once
#include "graph/graph.hpp"
#include "template/template.hpp"

template <class T, class U>
std::vector<T> dijkstra(const Graph<T> &g, const std::vector<U> &potentials, int s = 0,
                        T inf = std::numeric_limits<T>::max()) {
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
    int n = g.size();
    std::vector<T> dists(n, inf);
    std::priority_queue<_node, std::vector<_node>, std::greater<>> p_que;
    dists[s] = T();
    p_que.emplace(s, T());
    while (!p_que.empty()) {
        auto node = p_que.top();
        p_que.pop();
        if (dists[node.to()] < node.dist()) continue;
        for (auto &e : g[node.to()]) {
            auto next_dist = node.dist() + e.weight() + potentials[node.to()] - potentials[e.to()];
            if (chmin(dists[e.to()], next_dist)) p_que.emplace(e.to(), next_dist);
        }
    }
    for (int i = 0; i < n; ++i) dists[i] += potentials[i] - potentials[s];
    return dists;
}
