#include "_base.hpp"
#include "graph/graph.hpp"

vector<int> tree_dist(const Graph<void> &g, int r = 0) {
    struct S {
        int idx, p, d;
    };
    vector<int> res(g.size());
    stack<S> st;
    st.push({r, -1, 0});
    while (!st.empty()) {
        auto [idx, p, d] = st.top();
        st.pop();
        res[idx] = d;
        for (auto i : g[idx]) {
            if (i == p) continue;
            st.push({i, idx, d + 1});
        }
    }
    return res;
}
