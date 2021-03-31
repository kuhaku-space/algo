#include "_base.hpp"

struct Tree {
    int V;
    vector<vector<int>> data;
    vector<int> parent;

    Tree(int v) : V(v), data(v), parent(v) {}

    void init(int r = 0) {
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

    void build(int r = 0) { init(r); }

    void add_edge(int a, int b) {
        data[a].emplace_back(b);
        data[b].emplace_back(a);
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
