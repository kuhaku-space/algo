#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
#include "graph/graph.hpp"
#include "template/template.hpp"

template <class T>
std::pair<std::vector<T>, std::vector<int>> dijkstra(const Graph<T> &g, int s = 0,
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
    std::vector<T> dists(g.size(), inf);
    std::vector<int> v(g.size(), -1);
    std::priority_queue<_node, std::vector<_node>, std::greater<>> p_que;
    dists[s] = T();
    p_que.emplace(s, T());
    while (!p_que.empty()) {
        auto node = p_que.top();
        p_que.pop();
        if (dists[node.to()] < node.dist()) continue;
        for (auto &e : g[node.to()]) {
            if (chmin(dists[e.to()], node.dist() + e.weight())) {
                v[e.to()] = node.to();
                p_que.emplace(e.to(), node.dist() + e.weight());
            }
        }
    }
    return {dists, v};
}

int main(void) {
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    Graph<std::int64_t> g(n);
    g.input_edge(m, 0);
    auto &&[dist, v] = dijkstra(g, s, INF);
    if (dist[t] == INF) {
        std::cout << -1 << '\n';
    } else {
        std::vector<std::pair<int, int>> ans;
        int idx = t;
        while (idx != s) {
            ans.emplace_back(v[idx], idx);
            idx = v[idx];
        }
        std::reverse(ans.begin(), ans.end());
        std::cout << dist[t] << ' ' << ans.size() << '\n';
        for (auto p : ans) std::cout << p.first << ' ' << p.second << '\n';
    }
    return 0;
}
