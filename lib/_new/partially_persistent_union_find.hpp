#include "template/template.hpp"

/**
 * @brief 部分永続Union-Find
 * 
 */
struct partially_persistent_union_find {
    partially_persistent_union_find(int _n) : now(0), data(_n, -1), time(_n, 0) {}

    int root(int x, int t) const {
        if (data[x] < 0 || time[x] > t) return x;
        return root(data[x], t);
    }

    int unite(int x, int y) {
        ++now;
        x = root(x, now), y = root(y, now);
        if (x == y) return now;
        if (data[x] > data[y]) swap(x, y);
        time[y] = now;
        data[x] += data[y];
        data[y] = x;
        return now;
    }

    int size(int x) const { return -data[root(x, now)]; }

    bool same(int x, int y, int t) const { return root(x, t) == root(y, t); }

  private:
    int now;
    vector<int> data;
    vector<int> time;
};
