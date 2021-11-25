#include "template/template.hpp"

/**
 * @brief 素集合データ構造
 *
 */
struct union_find {
    vector<int> data;
    vector<int> edge;

    union_find() : data(), edge() {}
    union_find(int _n) : data(_n, -1), edge(_n, 0) {}

    int root(int x) { return this->data[x] < 0 ? x : this->data[x] = this->root(this->data[x]); }

    bool is_root(int x) { return this->data[x] < 0; }

    void unite(int x, int y) {
        x = this->root(x), y = this->root(y);
        if (x != y) {
            if (this->data[x] > this->data[y]) swap(x, y);
            this->data[x] += this->data[y];
            this->edge[x] += this->edge[y];
            this->data[y] = x;
        }
        ++(this->edge[x]);
    }

    int size(int x) { return -(this->data[this->root(x)]); }
    int get_size(int x) { return this->size(x); }
    int get_edge_size(int x) { return edge[x]; }

    bool same(int x, int y) { return this->root(x) == this->root(y); }
    bool is_same(int x, int y) { return this->same(x, y); }
};