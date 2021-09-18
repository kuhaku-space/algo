#include "_base.hpp"
#include "graph/graph.hpp"

// verify : https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_A 21/02/24

template <class T>
bool is_cycle(const Graph<T> &g) {
    int n = g.size();
    vector<bool> is_seen(n), is_finish(n);
    bool res = false;

    auto dfs = [&](auto self, int idx) {
        if (is_finish[idx]) return;
        is_seen[idx] = true;
        for (auto &e : g[idx]) {
            if (res |= is_seen[e.to]) return;
            self(self, e.to);
        }
        is_seen[idx] = false;
        is_finish[idx] = true;
    };

    for (int i = 0; i < n; ++i) {
        is_seen.assign(n, false);
        dfs(dfs, i);
    }
    return res;
}

// verify : https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_B 21/02/24

template <class T>
vector<int> topological_sort(const Graph<T> &g) {
    int n = g.size();
    vector<int> res;
    vector<bool> is_seen(n);
    auto dfs = [&](auto self, int v) {
        if (is_seen[v]) return;
        is_seen[v] = true;
        for (auto &e : g[v])
            if (!is_seen[e.to]) self(self, e.to);
        res.emplace_back(v);
    };
    for (int i = 0; i < n; ++i) dfs(dfs, i);
    reverse(res.begin(), res.end());
    return res;
}
