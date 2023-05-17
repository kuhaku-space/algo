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
        auto it = std::lower_bound(dp.begin(), dp.end(), x);
        if (it == dp.end()) dp.emplace_back(x);
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
    std::vector<std::pair<T, int>> dp;
    std::vector<int> pr(n, -1);
    for (int i = 0; i < n; ++i) {
        std::pair<T, int> p(v[i], -i);
        auto it = std::lower_bound(dp.begin(), dp.end(), p);
        if (it != dp.begin()) pr[i] = -std::prev(it)->second;
        if (it == dp.end()) dp.emplace_back(p);
        else *it = p;
    }

    std::vector<int> res;
    for (int x = -dp.back().second; x != -1; x = pr[x]) {
        res.emplace_back(x);
    }
    std::reverse(res.begin(), res.end());
    return res;
}
