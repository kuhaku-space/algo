#include "lib/template/template.hpp"

// reference :
// https://github.com/beet-aizu/library/blob/master/tree/eulertourforvertex.cpp

struct eular_tour {
    vector<vector<int>> G;
    vector<int> ls, rs;
    int pos;

    eular_tour(int n) : G(n), ls(n), rs(n) {}

    pair<int, int> operator[](int i) const { return {ls[i], rs[i]}; }

    int size() const { return pos; }

    void add_edge(int a, int b) {
        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }

    void dfs(int v, int p) {
        ls[v] = pos++;
        for (auto &u : G[v]) {
            if (u != p) dfs(u, v);
            rs[v] = pos;
        }
    }

    void build(int r = 0) {
        pos = 0;
        dfs(r, -1);
    }

    int get_l(int i) const { return ls[i]; }
    int get_r(int i) const { return rs[i]; }

    template <class F>
    void query(int v, const F &f) {
        f(ls[v], rs[v]);
    }
};
