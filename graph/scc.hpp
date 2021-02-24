#include "_base.hpp"
#include "graph/graph.hpp"

// verify : https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_C 21/02/24

template <class T>
vector<int> SCC(const Graph<T> &g) {
    int n = g.size();
    Graph<T> rg(n);
    vector<int> comp(n, -1), order;
    bitset<1 << 20> used;

    for (auto &es : g) {
        for (auto &e : es) rg.add_edge(e.to, e.from);
    }

    auto dfs = [&](auto self, int idx) {
        if (used[idx]) return;
        used.set(idx);
        for (auto &e : g[idx]) self(self, e.to);
        order.emplace_back(idx);
    };
    auto rdfs = [&](auto self, int idx, int cnt) {
        if (~comp[idx]) return;
        comp[idx] = cnt;
        for (auto &e : rg[idx]) self(self, e.to, cnt);
    };

    for (int i = 0; i < n; i++) dfs(dfs, i);
    reverse(order.begin(), order.end());
    int ptr = 0;
    for (auto i : order) {
        if (comp[i] == -1) rdfs(rdfs, i, ptr++);
    }

    return comp;
};

template <class T>
Graph<T> make_DAG(const Graph<T> &g, const vector<int> &v) {
    int n = *max_element(v.begin(), v.end()) + 1;
    Graph<T> res(n);
    for (auto &es : g) {
        for (auto &e : es) {
            int x = v[e.from], y = v[e.to];
            if (x != y) res.add_edge(x, y, e.dist);
        }
    }
    return res;
}
