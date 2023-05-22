#include "data_structure/persistent_array.hpp"
#include "template/template.hpp"

/**
 * @brief 永続Union-Find
 *
 */
struct persistent_union_find {
    constexpr persistent_union_find() : data() {}
    persistent_union_find(const persistent_array<int> &_data) : data(_data) {}
    persistent_union_find(int n) : data(n, -1) {}

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
        if (a > b) std::swap(x, y);
        return persistent_union_find(this->data.set(x, a + b).set(y, x));
    }

    int size(int x) const { return -(this->data[this->root(x)]); }
    int get_size(int x) const { return this->size(x); }

    bool same(int x, int y) const { return this->root(x) == this->root(y); }
    bool is_same(int x, int y) const { return this->same(x, y); }

  private:
    persistent_array<int> data;
};
