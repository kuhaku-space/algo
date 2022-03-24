#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"
#include "graph/graph.hpp"
#include "template/atcoder.hpp"

template <class T>
pair<vector<T>, vector<int>> dijkstra(const Graph<T> &g, int s = 0,
                                      T inf = numeric_limits<T>::max()) {
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
    vector<T> dists(g.size(), inf);
    vector<int> v(g.size(), -1);
    priority_queue<_node, vector<_node>, greater<>> p_que;
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
    sonic();
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    Graph<ll> g(n);
    g.input_edge(m, 0);
    auto [dist, v] = dijkstra(g, s, INF);

    if (dist[t] == INF) {
        co(-1);
    } else {
        vector<pair<int, int>> ans;
        int idx = t;
        while (idx != s) {
            ans.emplace_back(v[idx], idx);
            idx = v[idx];
        }
        reverse(ans.begin(), ans.end());
        co(dist[t], ans.size());
        for (auto p : ans) { co(p.first, p.second); }
    }
    return 0;
}
