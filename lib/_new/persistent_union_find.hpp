#include "_new/persistent_array.hpp"
#include "template/template.hpp"

struct persistent_union_find {
    constexpr persistent_union_find() : data() {}
    persistent_union_find(const persistent_array<int> &_data) : data(_data) {}
    persistent_union_find(int _n) : data(_n, -1) {}

    int root(int x) const {
        int y = this->data[x];
        return y < 0 ? x : this->root(y);
    }
    int get_root(int x) const { return this->root(x); }

    bool is_root(int x) const { return this->data[x] < 0; }

    persistent_union_find unite(int x, int y) {
        x = this->root(x), y = this->root(y);
        if (x == y) return *this;
        int a = this->data[x], b = this->data[y];
        if (a > b) { swap(x, y); }
        auto u = this->data.set(x, a + b);
        auto v = this->data.set(y, x);
        return persistent_union_find(v);
    }

    int size(int x) const { return -(this->data[this->root(x)]); }
    int get_size(int x) const { return this->size(x); }

    bool same(int x, int y) const { return this->root(x) == this->root(y); }
    bool is_same(int x, int y) const { return this->same(x, y); }

  private:
    persistent_array<int> data;
};
