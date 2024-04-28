#include <algorithm>
#include <cstdint>
#include <iterator>
#include "algorithm/compress.hpp"
#include "binary_tree/fenwick_tree.hpp"

/**
 * @brief 転倒数を求める
 *
 * @tparam T 配列の型
 * @param v 配列
 * @retval std::int64_t 転倒数
 */
template <class T>
std::int64_t inversion_number(const std::vector<T> &v) {
    if (v.empty()) return 0;
    auto u = compress(v);
    std::reverse(std::begin(u), std::end(u));
    fenwick_tree<T> bit(*max_element(std::begin(u), std::end(u)) + 1);
    std::int64_t res = 0;
    for (auto x : u) {
        res += bit.sum(x);
        bit.add(x, 1);
    }
    return res;
}
