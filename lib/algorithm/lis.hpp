#pragma once
#include <algorithm>
#include <iterator>
#include <vector>

/// @brief 最長増加部分列
template <class T>
int longest_increasing_subsequence(const std::vector<T> &v, bool strict = true) {
    int n = v.size();
    std::vector<T> dp;
    for (auto x : v) {
        auto it = (strict ? std::lower_bound(dp.begin(), dp.end(), x)
                          : std::upper_bound(dp.begin(), dp.end(), x));
        if (it == dp.end()) dp.emplace_back(x);
        else *it = x;
    }
    return dp.size();
}

/// @brief 最長増加部分列
template <class T>
std::vector<int> make_lis(const std::vector<T> &v) {
    int n = v.size();
    std::vector<T> dp;
    std::vector<int> pos;
    pos.reserve(n);
    for (auto x : v) {
        auto it = std::lower_bound(dp.begin(), dp.end(), x);
        pos.emplace_back(std::distance(dp.begin(), it));
        if (it == dp.end()) dp.emplace_back(x);
        else *it = x;
    }

    int x = dp.size();
    std::vector<int> res(x--);
    for (int i = n - 1; i >= 0; --i) {
        if (pos[i] == x) res[x] = i, --x;
    }
    return res;
}
