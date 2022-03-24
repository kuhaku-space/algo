#pragma once
#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief ダイクストラ法
 *
 * @tparam T 辺の重みの型
 * @param g グラフ
 * @param s 始点
 * @param inf 正の無限表現
 * @retval std::vector<T> 各頂点までの最短距離
 */
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
            if (chmin(dists[e.to()], node.dist() + e.weight()))
                p_que.emplace(e.to(), node.dist() + e.weight());
        }
    }
    return dists;
}
