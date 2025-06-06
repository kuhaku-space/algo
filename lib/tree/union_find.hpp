#pragma once
#include <concepts>
#include <utility>
#include <vector>

/// @brief 素集合データ構造
/// @details Implement (union by size) + (path compression)
/// @see https://github.com/atcoder/ac-library/blob/master/atcoder/dsu.hpp
struct union_find {
    union_find() = default;
    explicit union_find(int _n) : _rank(_n), data(_n, -1) {}

    const int &operator[](std::size_t x) const { return data[x]; }
    int &operator[](std::size_t x) { return data[x]; }

    int root(int x) { return data[x] < 0 ? x : data[x] = root(data[x]); }
    int get_root(int x) { return root(x); }

    bool is_root(int x) const { return data[x] < 0; }

    bool same(int x, int y) { return root(x) == root(y); }
    bool is_same(int x, int y) { return same(x, y); }

    int rank() { return _rank; }

    int size(int x) { return -(data[root(x)]); }
    int get_size(int x) { return size(x); }

    std::vector<int> leaders() {
        std::vector<int> res;
        for (int i = 0; i < (int)data.size(); ++i) {
            if (is_root(i)) res.emplace_back(i);
        }
        return res;
    }

    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        --_rank;
        if (data[x] > data[y]) std::swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    template <class F>
    requires std::invocable<F, int, int, bool>
    bool unite(int x, int y, F f) {
        x = root(x), y = root(y);
        bool swapped = false;
        if (x != y) {
            if (data[x] > data[y]) std::swap(x, y), swapped = true;
            data[x] += data[y];
            data[y] = x;
        }
        f(x, y, swapped);
        return x != y;
    }

    template <class F>
    requires std::invocable<F, int, int>
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
    int _rank;
    std::vector<int> data;
};
