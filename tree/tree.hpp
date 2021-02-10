#include "_base.hpp"

struct Tree {
    int64_t V;
    vector<vector<int64_t>> data;
    vector<int64_t> depth;
    vector<int64_t> parent;

    Tree(int64_t v) : V(v) {
        data = vector<vector<int64_t>>(V);
        depth = vector<int64_t>(V);
        parent = vector<int64_t>(V);
    }

    void init(int64_t r) {
        struct node {
            int64_t v, p, d;
        };
        stack<node> st;
        st.push(node{r, -1, 0});
        while (!st.empty()) {
            auto [v, p, d] = st.top();
            st.pop();
            depth[v] = d;
            parent[v] = p;
            for (auto i : data[v]) {
                if (i == p) continue;
                st.push(node{i, v, d + 1});
            }
        }
    }

    void build(int64_t r = 0) { init(r); }

    void add_edge(int64_t a, int64_t b) {
        data[a].emplace_back(b);
        data[b].emplace_back(a);
    }

    void bfs(int64_t s) {
        struct node {
            int64_t v, p;
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

    void dfs(int64_t v, int64_t p) {
        for (auto i : data[v]) {
            if (i == p) continue;
            dfs(i, v);
        }
    }
};
