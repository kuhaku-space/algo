#pragma once
#include <algorithm>
#include <cstdint>
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
