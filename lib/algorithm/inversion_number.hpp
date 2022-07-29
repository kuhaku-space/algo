#include "algorithm/compress.hpp"
#include "binary_tree/BIT.hpp"
#include "template/template.hpp"

/**
 * @brief 転倒数を求める
 *
 * @tparam T 配列の型
 * @param v 配列
 * @retval std::int64_t 転倒数
 */
template <class T>
std::int64_t inversion_number(const std::vector<T> &v) {
    auto u = compress(v);
    std::reverse(u.begin(), u.end());
    BIT<T> bit(*max_element(u.begin(), u.end()) + 1);
    std::int64_t res = 0;
    for (auto x : u) {
        res += bit.sum(x);
        bit.add(x, 1);
    }
    return res;
}
