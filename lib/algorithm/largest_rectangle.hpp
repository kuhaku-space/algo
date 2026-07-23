#pragma once
#include <algorithm>
#include <stack>
#include <utility>
#include <vector>

/// @brief ヒストグラムの中に含まれる最大長方形の面積
/// @complexity O(N)
template <class T, class U = T>
U largest_rectangle(const std::vector<T> &v) {
    int n = v.size();
    std::stack<std::pair<T, int>> st;
    U res = U();
    for (int i = 0; i < n; ++i) {
        int l = i;
        while (!st.empty() && v[i] < st.top().first) {
            auto [h, j] = st.top();
            st.pop();
            l = j;
            res = std::max(res, (U)h * (i - j));
        }
        if (v[i] != T() && (st.empty() || st.top().first < v[i])) st.emplace(v[i], l);
    }
    while (!st.empty()) {
        auto [h, j] = st.top();
        st.pop();
        res = std::max(res, (U)h * (n - j));
    }
    return res;
}
