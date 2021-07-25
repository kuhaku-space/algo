#include "_base.hpp"

struct union_find {
    vector<int> data;

    union_find(int _n) : data(_n) {}

    int root(int x) {
        return data[x] < 0 ? x : data[x] = root(data[x]);
    }

    void unite(int x, int y) {
        x = root(x), y = root(y);
        if (x != y) {
            if (data[y] < data[x]) swap(x, y);
            data[y] = x;
            data[x] += data[y];
        }
    }

    int size(int x) { return -data[root(x)]; }

    bool same(int x, int y) { return root(x) == root(y); }
};
