#include "_base.hpp"

struct union_find {
    int64_t now;
    vector<int64_t> parent;
    vector<int64_t> size;
    vector<int64_t> time;

    union_find(int64_t _n) : now(0), size(_n, 1), time(_n, 0) {
        for (int64_t i = 0; i < _n; ++i) parent.emplace_back(i);
    }

    int64_t root(int64_t x, int64_t t) const {
        if (time[x] > t) return x;
        return root(parent[x], t);
    }

    int64_t unite(int64_t x, int64_t y) {
        ++now;
        x = root(now, x), y = root(now, y);
        if (x == y) return now;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        time[y] = now;
        size[x] += size[y];
        return now;
    }

    int64_t get_size(int64_t x) const { return size[root(x, now)]; }

    bool is_same(int64_t x, int64_t y, int64_t t) const {
        return root(x, t) == root(y, t);
    }
};
