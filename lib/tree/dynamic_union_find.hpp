#include "template/template.hpp"

/**
 * @brief 動的Union-Find
 *
 */
struct dynamic_union_find {
    dynamic_union_find() : data() {}

    int root(int x) {
        if (!data.count(x)) data[x] = -1;
        return data[x] < 0 ? x : data[x] = root(data[x]);
    }
    int get_root(int x) { return root(x); }

    bool is_root(int x) { return data.count(x) && data[x] < 0; }

    bool same(int x, int y) { return root(x) == root(y); }
    bool is_same(int x, int y) { return same(x, y); }

    int size(int x) { return -(data[root(x)]); }
    int get_size(int x) { return size(x); }

    void clear() { data.clear(); }

    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        if (data[x] > data[y]) std::swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    template <class F>
    bool unite(int x, int y, F f) {
        x = root(x), y = root(y);
        if (x != y) {
            if (data[x] > data[y]) std::swap(x, y);
            data[x] += data[y];
            data[y] = x;
        }
        f(x, y);
        return x != y;
    }

  private:
    std::unordered_map<int, int> data;
};
