#include "template/template.hpp"

struct Tree {
    int V, logV;
    vector<vector<int>> data;
    vector<int> depth;
    vector<vector<int>> parent;

    Tree(int v) : V(v), logV(0) {
        while (V > (1LL << logV)) ++logV;
        data = vector<vector<int>>(V);
        depth = vector<int>(V);
        parent = vector<vector<int>>(logV, vector<int>(V));
    }

    void init(int r) {
        struct node {
            int v, p, d;
        };
        stack<node> st;
        st.push(node{r, -1, 0});
        while (!st.empty()) {
            auto [v, p, d] = st.top();
            st.pop();
            depth[v] = d;
            parent[0][v] = p;
            for (auto i : data[v]) {
                if (i == p) continue;
                st.push(node{i, v, d + 1});
            }
        }
    }

    void build(int r = 0) {
        this->init(r);
        for (int k = 0; k < logV - 1; ++k) {
            for (int v = 0; v < V; ++v) {
                if (parent[k][v] < 0)
                    parent[k + 1][v] = -1;
                else
                    parent[k + 1][v] = parent[k][parent[k][v]];
            }
        }
    }

    void add_edge(int a, int b) {
        data[a].emplace_back(b);
        data[b].emplace_back(a);
    }

    int lca(int u, int v) {
        if (depth[u] > depth[v]) swap(u, v);
        for (int k = 0; k < logV; ++k) {
            if ((depth[v] - depth[u]) >> k & 1) v = parent[k][v];
        }
        if (u == v) return u;

        for (int k = logV - 1; k >= 0; --k) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    int get_depth(int a) { return depth[a]; }
    int get_parent(int a) { return parent[0][a]; }

    int get_ancestor(int a, int d) {
        for (int k = 0; d; d >>= 1, ++k) {
            if (d & 1) a = parent[k][a];
        }
        return a;
    }
};
