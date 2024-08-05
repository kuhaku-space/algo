#include <stack>
#include <vector>
#include "graph/graph.hpp"

/// @brief なもりグラフ上のサイクル検出
template <class T>
std::vector<int> cycle_detection_on_namori_graph(const Graph<T> &g) {
    int n = g.size();
    std::vector<int> cnt(n);
    std::stack<int> st;
    for (int i = 0; i < n; ++i) {
        cnt[i] = g[i].size();
        if (cnt[i] == 1) st.emplace(i);
    }
    while (!st.empty()) {
        int x = st.top();
        st.pop();
        for (auto &e : g[x]) {
            if ((--cnt[e.to()]) == 1) st.emplace(e.to());
        }
    }

    std::vector<int> parent(n, -2);
    st = std::stack<int>();
    for (int i = 0; i < n; ++i) {
        if (cnt[i] >= 2) {
            parent[i] = -1;
            st.emplace(i);
        }
    }

    while (!st.empty()) {
        int x = st.top();
        st.pop();
        for (auto &e : g[x]) {
            if (parent[e.to()] == -2) {
                parent[e.to()] = x;
                st.emplace(e.to());
            }
        }
    }

    return parent;
}
