#pragma once
#include <vector>

/// @brief Cartesian Tree
template <typename T>
std::vector<int> cartesian_tree(const std::vector<T> &v) {
    int n = v.size();
    std::vector<int> res(n, -1);
    std::vector<int> st;
    st.reserve(n);
    for (int i = 0; i < n; ++i) {
        int p = -1;
        while (!st.empty() && v[i] < v[st.back()]) {
            p = st.back();
            st.pop_back();
        }
        if (p != -1) res[p] = i;
        if (!st.empty()) res[i] = st.back();
        st.emplace_back(i);
    }
    return res;
}

namespace internal {

struct node_t {
    int parent, left, right;

    constexpr node_t() : parent(-1), left(-1), right(-1) {}
};

}  // namespace internal

/// @brief Cartesian Tree
template <typename T>
std::vector<internal::node_t> cartesian_tree_fully(const std::vector<T> &v) {
    int n = v.size();
    std::vector<internal::node_t> res(n);
    std::vector<int> st;
    st.reserve(n);
    for (int i = 0; i < n; ++i) {
        int p = -1;
        while (!st.empty() && v[i] < v[st.back()]) p = st.back(), st.pop_back();
        if (p != -1) res[p].parent = i, res[i].left = p;
        if (!st.empty()) res[i].parent = st.back(), res[st.back()].right = i;
        st.emplace_back(i);
    }
    return res;
}
