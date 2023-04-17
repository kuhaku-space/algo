#include "template/template.hpp"

/**
 * @brief 動的Union-Find
 *
 */
struct dynamic_union_find {
    dynamic_union_find() : data() {}

    int root(int x) {
        if (!this->data.count(x)) this->data[x] = -1;
        return this->data[x] < 0 ? x : this->data[x] = this->root(this->data[x]);
    }
    int get_root(int x) { return this->root(x); }

    bool is_root(int x) { return this->data.count(x) && this->data[x] < 0; }

    bool same(int x, int y) { return this->root(x) == this->root(y); }
    bool is_same(int x, int y) { return this->same(x, y); }

    int size(int x) { return -(this->data[this->root(x)]); }
    int get_size(int x) { return this->size(x); }

    bool unite(int x, int y) {
        x = this->root(x), y = this->root(y);
        if (x == y) return false;
        if (this->data[x] > this->data[y]) swap(x, y);
        this->data[x] += this->data[y];
        this->data[y] = x;
        return true;
    }

    template <class F>
    bool unite(int x, int y, F f) {
        x = this->root(x), y = this->root(y);
        if (x != y) {
            if (this->data[x] > this->data[y]) swap(x, y);
            this->data[x] += this->data[y];
            this->data[y] = x;
        }
        f(x, y);
        return x != y;
    }

  private:
    std::unordered_map<int, int> data;
};
