#include <utility>
#include <vector>

/**
 * @brief 素集合データ構造
 * @details Implement (union by size) + (path compression)
 * @see https://github.com/atcoder/ac-library/blob/master/atcoder/dsu.hpp
 */
struct union_find {
    union_find() = default;
    explicit union_find(int _n) : data(_n, -1) {}

    int root(int x) { return data[x] < 0 ? x : data[x] = root(data[x]); }
    int get_root(int x) { return root(x); }

    bool is_root(int x) const { return data[x] < 0; }

    bool same(int x, int y) { return root(x) == root(y); }
    bool is_same(int x, int y) { return same(x, y); }

    int size(int x) { return -(data[root(x)]); }
    int get_size(int x) { return size(x); }

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
    std::vector<int> data;
};
