#include "_base.hpp"
#include "graph/graph.hpp"

// verify : https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_B 21/02/23

template <class T>
vector<int> topological_sort(const Graph<T> &g) {
    int n = g.size();
    vector<int> res;
    bitset<1 << 20> is_seen;
    auto dfs = [&](auto self, int v) {
        if (is_seen[v]) continue;
        is_seen.set(v);
        for (auto &e : g.edges[v])
            if (!is_seen[e.to]) self(self, e.to);
        res.emplace_back(v);
    };
    for (int64_t i = 0; i < n; ++i) dfs(dfs, i);
    reverse(res.begin(), res.end());
    return res;
}
