#include "graph/graph.hpp"
#include "template/template.hpp"

template <class T>
vector<int> tree_parent(const Graph<T> &g, int r = 0) {
    struct S {
        int idx, p;
    };
    vector<int> res(g.size());
    stack<S> st;
    st.push({r, -1});
    while (!st.empty()) {
        auto [idx, p] = st.top();
        st.pop();
        res[idx] = p;
        for (auto i : g[idx]) {
            if (i.to == p) continue;
            st.emplace(i.to, idx);
        }
    }
    return res;
}

template<>
vector<int> tree_parent(const Graph<void> &g, int r = 0) {
    struct S {
        int idx, p;
    };
    vector<int> res(g.size());
    stack<S> st;
    st.push({r, -1});
    while (!st.empty()) {
        auto [idx, p] = st.top();
        st.pop();
        res[idx] = p;
        for (auto i : g[idx]) {
            if (i == p) continue;
            st.emplace(i, idx);
        }
    }
    return res;
}
