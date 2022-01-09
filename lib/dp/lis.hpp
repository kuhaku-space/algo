#include "template/template.hpp"

/**
 * @brief 最長増加部分列
 * 
 * @tparam T 配列の型
 * @param v 配列
 * @return int 最長増加部分列の長さ
 */
template <class T>
int LIS(const vector<T> &v) {
    int n = v.size();
    vector<T> dp;
    for (int i = 0; i < n; ++i) {
        auto it = lower_bound(dp.begin(), dp.end(), v[i]);
        if (it == dp.end())
            dp.emplace_back(v[i]);
        else
            *it = v[i];
    }
    return dp.size();
}
