#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief 木の頂点の親を求める
 * 
 * @tparam T 辺の重みの型
 * @param g 木
 * @param r 根
 * @return std::vector<int> 
 */
template <class T>
std::vector<int> tree_parent(const Graph<T> &g, int r = 0) {
    std::vector<int> res(g.size());
    std::stack<std::pair<int, int>> st;
    res[r] = -1;
    st.emplace(r, -1);
    while (!st.empty()) {
        auto [index, parent] = st.top();
        st.pop();
        for (auto &e : g[index]) {
            if (e.to() == parent) continue;
            res[e.to()] = index;
            st.emplace(e.to(), index);
        }
    }
    return res;
}
