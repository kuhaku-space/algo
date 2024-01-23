#include <stack>
#include <vector>

/**
 * @brief Cartesian Tree
 *
 * @tparam T 配列の型
 * @param v 配列
 * @return std::vector<int>
 */
template <typename T>
std::vector<int> cartesian_tree(const std::vector<T> &v) {
    int n = v.size();
    std::vector<int> res(n, -1);
    std::stack<T> st;
    for (int i = 0; i < n; ++i) {
        int p = -1;
        while (!st.empty() && v[i] < v[st.top()]) {
            p = st.top();
            st.pop();
        }
        if (p != -1) res[p] = i;
        if (!st.empty()) res[i] = st.top();
        st.emplace(i);
    }
    return res;
}
