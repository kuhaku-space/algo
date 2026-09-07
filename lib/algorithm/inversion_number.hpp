#pragma once
#include <algorithm>
#include <cstdint>
#include <numeric>
#include <vector>
#include "algorithm/compress.hpp"
#include "data_structure/fenwick_tree.hpp"

/// @brief 転倒数
/// @param v 対象の列
/// @return `i < j` かつ `v[i] > v[j]` となる添字対の個数
/// @complexity 要素数を $n$ として $O(n\log n)$
template <class T>
std::int64_t inversion_number(const std::vector<T> &v) {
    if (v.empty()) return 0;
    auto ids = compress(v);
    int n = ids.size();
    FenwickTree<int> ft(*std::max_element(ids.begin(), ids.end()) + 1);
    std::int64_t res = 0;
    for (int i = n - 1; i >= 0; --i) {
        res += ft.sum(ids[i]);
        ft.add(ids[i], 1);
    }
    return res;
}

/// @brief 順列の転倒数
/// @details 座標圧縮を省くので `inversion_number` より定数倍が軽い。
/// @param v 0 以上 n 未満の整数の順列
/// @pre `v` は 0 以上 n 未満の整数の順列
/// @return `i < j` かつ `v[i] > v[j]` となる添字対の個数
/// @complexity 要素数を $n$ として $O(n\log n)$
template <class T>
std::int64_t inversion_number_of_permutation(const std::vector<T> &v) {
    if (v.empty()) return 0;
    int n = v.size();
    FenwickTree<int> ft(n);
    std::int64_t res = 0;
    for (int i = n - 1; i >= 0; --i) {
        res += ft.sum(v[i]);
        ft.add(v[i], 1);
    }
    return res;
}

/// @brief 隣接スワップの最小回数
/// @param a 変換元の列
/// @param b 変換先の列
/// @return 隣接要素の交換で `a` を `b` にする最小回数。多重集合として一致しなければ -1
/// @complexity 要素数を $n$ として $O(n\log n)$
template <class T>
std::int64_t adjacent_swap_distance(const std::vector<T> &a, const std::vector<T> &b) {
    if (a.size() != b.size()) return -1;
    int n = a.size();
    std::vector<int> order_a(n), order_b(n);
    std::iota(order_a.begin(), order_a.end(), 0);
    std::iota(order_b.begin(), order_b.end(), 0);
    std::stable_sort(order_a.begin(), order_a.end(), [&a](int x, int y) { return a[x] < a[y]; });
    std::stable_sort(order_b.begin(), order_b.end(), [&b](int x, int y) { return b[x] < b[y]; });
    std::vector<int> perm(n);
    for (int i = 0; i < n; ++i) {
        if (a[order_a[i]] != b[order_b[i]]) return -1;
        perm[order_a[i]] = order_b[i];
    }
    return inversion_number_of_permutation(perm);
}
