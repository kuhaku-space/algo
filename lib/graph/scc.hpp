#include "template/template.hpp"
#include "graph/graph.hpp"

// verify : https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_C 21/02/24

template <class T>
vector<int> scc(const Graph<T> &g) {
    int n = g.size();
    Graph<T> rg(n);
    vector<int> comp(n, -1), order;
    vector<bool> used(n);

    for (auto &es : g) {
        for (auto &e : es) rg.add_edge(e.to, e.from);
    }

    auto dfs = [&](auto self, int idx) {
        if (used[idx]) return;
        used[idx] = true;
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
    Graph<T> res(*max_element(v.begin(), v.end()) + 1);
    for (auto &es : g) {
        for (auto &e : es) {
            int x = v[e.from], y = v[e.to];
            if (x != y) res.add_edge(x, y, e.dist);
        }
    }
    return res;
}

vector<int> scc(const Graph<void> &g) {
    int n = g.size();
    Graph<void> rg(n);
    vector<int> comp(n, -1), order;
    vector<bool> used(n);

    for (int i = 0; i < n; ++i) {
        for (auto &e : g[i]) rg.add_edge(e, i);
    }

    auto dfs = [&](auto self, int idx) {
        if (used[idx]) return;
        used[idx] = true;
        for (auto &e : g[idx]) self(self, e);
        order.emplace_back(idx);
    };
    auto rdfs = [&](auto self, int idx, int cnt) {
        if (~comp[idx]) return;
        comp[idx] = cnt;
        for (auto &e : rg[idx]) self(self, e, cnt);
    };

    for (int i = 0; i < n; i++) dfs(dfs, i);
    reverse(order.begin(), order.end());
    int ptr = 0;
    for (auto i : order) {
        if (comp[i] == -1) rdfs(rdfs, i, ptr++);
    }

    return comp;
};

Graph<void> make_DAG(const Graph<void> &g, const vector<int> &v) {
    int n = g.size();
    Graph<void> res(*max_element(v.begin(), v.end()) + 1);
    for (int i = 0; i < n; ++i) {
        for (auto &e : g[i]) {
            int x = v[i], y = v[e];
            if (x != y) res.add_edge(x, y);
        }
    }
    return res;
}
