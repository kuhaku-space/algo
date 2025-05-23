#pragma once
#include <algorithm>
#include <cstdint>
#include <numeric>
#include <vector>
#include "algorithm/compress.hpp"
#include "binary_tree/fenwick_tree.hpp"

/// @brief 転倒数
template <class T>
std::int64_t inversion_number(const std::vector<T> &v) {
    if (v.empty()) return 0;
    auto u = compress(v);
    std::reverse(u.begin(), u.end());
    fenwick_tree<T> bit(*std::max_element(u.begin(), u.end()) + 1);
    std::int64_t res = 0;
    for (auto x : u) {
        res += bit.sum(x);
        bit.add(x, 1);
    }
    return res;
}

/// @brief 転倒数
template <class T>
std::int64_t inversion_number_of_permutation(const std::vector<T> &v) {
    if (v.empty()) return 0;
    int n = v.size();
    fenwick_tree<T> bit(n);
    std::int64_t res = 0;
    for (int i = n - 1; i >= 0; --i) {
        res += bit.sum(v[i]);
        bit.add(v[i], 1);
    }
    return res;
}

/// @brief 最小隣接スワップ回数
template <class T>
std::int64_t swap_distance(const std::vector<T> &a, const std::vector<T> &b) {
    if (a.size() != b.size()) return -1;
    int n = a.size();
    std::vector<int> c(n), d(n);
    std::iota(c.begin(), c.end(), 0);
    std::iota(d.begin(), d.end(), 0);
    std::stable_sort(c.begin(), c.end(), [&a](int x, int y) { return a[x] < a[y]; });
    std::stable_sort(d.begin(), d.end(), [&b](int x, int y) { return b[x] < b[y]; });
    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        int x = c[i], y = d[i];
        if (a[x] != b[y]) return -1;
        p[x] = y;
    }
    return inversion_number_of_permutation(p);
}
