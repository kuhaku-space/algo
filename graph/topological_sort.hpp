#include "_base.hpp"
#include "graph/graph.hpp"

// verify : https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_A 21/02/24

template <class T>
bool is_cycle(const Graph<T> &g) {
    int n = g.size();
    bitset<1 << 20> is_seen, is_finish;
    bool res = false;

    auto dfs = [&](auto self, int idx) {
        if (is_finish[idx]) return;
        is_seen.set(idx);
        for (auto &e : g[idx]) {
            if (res |= is_seen[e.to]) return;
            self(self, e.to);
        }
        is_seen.reset(idx);
        is_finish.set(idx);
    };

    for (int i = 0; i < n; ++i) {
        is_seen.reset();
        dfs(dfs, i);
    }
    return res;
}

// verify : https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_B 21/02/24

template <class T>
vector<int> topological_sort(const Graph<T> &g) {
    int n = g.size();
    vector<int> res;
    bitset<1 << 20> is_seen;
    auto dfs = [&](auto self, int v) {
        if (is_seen[v]) return;
        is_seen.set(v);
        for (auto &e : g[v])
            if (!is_seen[e.to]) self(self, e.to);
        res.emplace_back(v);
    };
    for (int i = 0; i < n; ++i) dfs(dfs, i);
    reverse(res.begin(), res.end());
    return res;
}
