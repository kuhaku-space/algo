#pragma once
#include <utility>
#include "persistent_ds/persistent_array.hpp"

/// @brief 永続Union-Find
struct persistent_union_find {
    constexpr persistent_union_find() : data() {}
    persistent_union_find(const persistent_array<int> &_data) : data(_data) {}
    persistent_union_find(int n) : data(n, -1) {}

    int root(int x) const {
        int y = data[x];
        return y < 0 ? x : root(y);
    }
    int get_root(int x) const { return root(x); }

    bool is_root(int x) const { return data[x] < 0; }

    persistent_union_find unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return *this;
        int a = data[x], b = data[y];
        if (a > b) std::swap(x, y);
        return persistent_union_find(data.set(x, a + b).set(y, x));
    }

    int size(int x) const { return -(data[root(x)]); }
    int get_size(int x) const { return size(x); }

    bool same(int x, int y) const { return root(x) == root(y); }
    bool is_same(int x, int y) const { return same(x, y); }

  private:
    persistent_array<int> data;
};
