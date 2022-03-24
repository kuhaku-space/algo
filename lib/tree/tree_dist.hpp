#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief 木の距離を求める
 *
 * @tparam T 辺の重みの型
 * @param g 木
 * @param r 根
 * @return std::vector<int>
 */
template <class T>
std::vector<int> tree_dist(const Graph<T> &g, int r = 0) {
    std::vector<int> res(g.size());
    std::stack<std::pair<int, int>> st;
    res[r] = 0;
    st.emplace(r, -1);
    while (!st.empty()) {
        auto [index, parent] = st.top();
        st.pop();
        for (auto &e : g[index]) {
            if (e.to() == parent) continue;
            res[e.to()] = res[index] + e.weight();
            st.emplace(e.to(), index);
        }
    }
    return res;
}
