#include "lib/template/template.hpp"

/*
 * verify :
 * https://atcoder.jp/contests/abc214/tasks/abc214_d 21/08/15
 */

struct union_find {
    vector<int> data;

    union_find(int _n) : data(_n, -1) {}

    int root(int x) { return data[x] < 0 ? x : data[x] = this->root(data[x]); }

    bool is_root(int x) { return data[x] < 0; }

    void unite(int x, int y) {
        x = this->root(x), y = this->root(y);
        if (x != y) {
            if (data[x] > data[y]) swap(x, y);
            data[x] += data[y];
            data[y] = x;
        }
    }

    int size(int x) { return -data[this->root(x)]; }

    bool same(int x, int y) { return this->root(x) == this->root(y); }
};