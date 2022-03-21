#include "template/template.hpp"
#include "graph/graph.hpp"

template <class T>
struct Tree {
    Graph<T> g;
    vector<int> parent;

    Tree(const Graph<T> &_g, int r = 0) : g(_g), parent(_g.size()) { build(r) }

    void build(int r = 0) {
        struct node {
            int v, p, d;
        };
        stack<node> st;
        st.push(node{r, -1, 0});
        while (!st.empty()) {
            auto [v, p, d] = st.top();
            st.pop();
            parent[v] = p;
            for (auto i : data[v]) {
                if (i == p) continue;
                st.push(node{i, v, d + 1});
            }
        }
    }

    void bfs(int s) {
        struct node {
            int v, p;
        };
        stack<node> st;
        st.push(node{s, -1});
        while (!st.empty()) {
            auto [v, p] = st.top();
            st.pop();
            parent[v] = p;
            for (auto i : data[v]) {
                if (i == p) continue;
                st.push(node{i, v});
            }
        }
    }

    void dfs(int v, int p) {
        for (auto i : data[v]) {
            if (i == p) continue;
            dfs(i, v);
        }
    }
};
