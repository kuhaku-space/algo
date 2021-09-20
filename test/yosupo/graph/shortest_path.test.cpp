#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"
#include "graph/graph.hpp"
#include "template/atcoder.hpp"

template <class T>
pair<vector<T>, vector<int>> dijkstra(const Graph<T> &g, int s = 0,
                                      T inf = numeric_limits<T>::max()) {
    struct _edge {
        int to;
        T dist;
        bool operator<(const _edge &rhs) const { return dist < rhs.dist; }
        bool operator>(const _edge &rhs) const { return rhs < *this; }
    };
    vector<T> dist(g.size(), inf);
    vector<int> v(g.size(), -1);
    priority_queue<_edge, vector<_edge>, greater<_edge>> p_que;
    dist[s] = T();
    p_que.push(_edge{s, T()});
    while (!p_que.empty()) {
        _edge e = p_que.top();
        p_que.pop();
        if (dist[e.to] < e.dist) continue;
        for (auto &i : g[e.to]) {
            if (chmin(dist[i.to], e.dist + i.dist)) {
                v[i.to] = e.to;
                p_que.push(_edge{i.to, e.dist + i.dist});
            }
        }
    }
    return {dist, v};
}

int main(void) {
    sonic();
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    Graph<ll> g(n);
    g.input_edge(m, true);
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
        for (auto p : ans) {
            co(p.first, p.second);
        }
    }
    return 0;
}
