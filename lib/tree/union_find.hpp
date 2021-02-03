#include "_base.hpp"

struct union_find {
    vector<int64_t> par;
    vector<int64_t> sz;

    union_find(int64_t _n) : par(_n), sz(_n, 1) {
        for (int64_t i = 0; i < _n; ++i) par[i] = i;
    }

    int64_t root(int64_t x) {
        if (par[x] == x) return x;
        return par[x] = root(par[x]);
    }

    void unite(int64_t x, int64_t y) {
        x = root(x), y = root(y);
        if (x != y) {
            if (sz[x] < sz[y]) swap(x, y);
            par[y] = x;
            sz[x] += sz[y];
        }
    }

    int64_t size(int64_t x) { return sz[root(x)]; }

    bool is_same(int64_t x, int64_t y) { return root(x) == root(y); }
};
