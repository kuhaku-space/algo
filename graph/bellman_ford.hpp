#include "_base.hpp"
#include "graph/graph.hpp"

template <class T>
vector<T> bellman_ford(const Graph<T> &g, int s = 0,
                       T inf = numeric_limits<T>::max()) {
    int n = g.size();
    vector<T> dist(n, inf);
    bitset<1 << 17> negative_cycle;
    dist[s] = T();
    bool flg = true;
    for (int cnt = 0; flg && cnt <= n * 2; ++cnt) {
        flg = false;
        for (int i = 0; i < n; ++i) {
            if (dist[i] == inf) continue;
            for (auto j : g.edges[i]) {
                if (chmin(dist[j.to], dist[i] + j.dist)) {
                    flg = true;
                    if (cnt >= n) negative_cycle.set(j.to);
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (negative_cycle[i]) dist[i] = -inf;
    }
    return dist;
}
