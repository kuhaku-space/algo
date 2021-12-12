#include "template/template.hpp"

/**
 * @brief 素集合データ構造
 *
 */
struct union_find {
    union_find() : data() {}
    union_find(int _n) : data(_n, -1) {}

    int root(int x) { return this->data[x] < 0 ? x : this->data[x] = this->root(this->data[x]); }
    int get_root(int x) { return this->root(x); }

    bool is_root(int x) { return this->data[x] < 0; }

    bool unite(int x, int y) {
        x = this->root(x), y = this->root(y);
        if (x == y) return false;
        if (this->data[x] > this->data[y]) swap(x, y);
        this->data[x] += this->data[y];
        this->data[y] = x;
        return true;
    }

    int size(int x) { return -(this->data[this->root(x)]); }
    int get_size(int x) { return this->size(x); }

    bool same(int x, int y) { return this->root(x) == this->root(y); }
    bool is_same(int x, int y) { return this->same(x, y); }

  private:
    vector<int> data;
};
