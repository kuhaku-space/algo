#include "_base.hpp"

struct union_find {
    vector<int> par;
    vector<int> sz;

    union_find(int _n) : par(_n), sz(_n, 1) { iota(par.begin(), par.end(), 0); }

    int root(int x) {
        if (par[x] == x) return x;
        return par[x] = root(par[x]);
    }

    void unite(int x, int y) {
        x = root(x), y = root(y);
        if (x != y) {
            if (sz[x] < sz[y]) swap(x, y);
            par[y] = x;
            sz[x] += sz[y];
        }
    }

    int size(int x) { return sz[root(x)]; }

    bool is_same(int x, int y) { return root(x) == root(y); }
};
