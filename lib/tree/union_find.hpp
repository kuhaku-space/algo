#include "_base.hpp"

struct union_find {
    vector<int64_t> par;
    vector<int64_t> size;

    union_find(int64_t _n) {
        par = vector<int64_t>(_n);
        for (int64_t i = 0; i < _n; ++i) par[i] = i;
        size = vector<int64_t>(_n, 1);
    }

    int64_t root(int64_t x) {
        if (par[x] == x) return x;
        return par[x] = root(par[x]);
    }

    void unite(int64_t x, int64_t y) {
        x = root(x), y = root(y);
        if (x != y) {
            if (size[x] < size[y]) swap(x, y);
            par[y] = x;
            size[x] += size[y];
        }
    }

    int64_t get_size(int64_t x) { return size[root(x)]; }

    bool is_same(int64_t x, int64_t y) { return root(x) == root(y); }
};
