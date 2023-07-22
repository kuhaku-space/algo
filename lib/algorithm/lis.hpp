#include "template/template.hpp"

/**
 * @brief 最長増加部分列
 *
 * @tparam T 配列の型
 * @param v 配列
 * @retval int 最長増加部分列の長さ
 */
template <class T>
int longest_increasing_subsequence(const std::vector<T> &v) {
    int n = v.size();
    std::vector<T> dp;
    for (auto x : v) {
        auto it = std::lower_bound(std::begin(dp), std::end(dp), x);
        if (it == std::end(dp)) dp.emplace_back(x);
        else *it = x;
    }
    return dp.size();
}

/**
 * @brief 最長増加部分列
 *
 * @tparam T 配列の型
 * @param v 配列
 * @retval std::vector<int> 最長増加部分列のインデックス
 */
template <class T>
std::vector<int> make_lis(const std::vector<T> &v) {
    int n = v.size();
    std::vector<T> dp;
    std::vector<int> pos;
    pos.reserve(n);
    for (auto x : v) {
        auto it = std::lower_bound(std::begin(dp), std::end(dp), x);
        pos.emplace_back(std::distance(std::begin(dp), it));
        if (it == std::end(dp)) dp.emplace_back(x);
        else *it = x;
    }

    int x = dp.size();
    std::vector<int> res(x--);
    for (int i = n - 1; i >= 0; --i) {
        if (pos[i] == x) res[x] = i, --x;
    }
    return res;
}
