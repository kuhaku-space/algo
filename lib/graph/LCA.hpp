#include "_base.hpp"

struct LCA {
    int64_t V, logV;
    vector<vector<int64_t>> data;
    vector<int64_t> depth;
    vector<vector<int64_t>> parent;
    
    LCA(int64_t v) {
        V = v;
        logV = 0;
        while (v > (1LL << logV)) logV++;
        depth = vector<int64_t>(V);
        parent = vector<vector<int64_t>>(logV, vector<int64_t>(V));
    }
    
    void init(int64_t v) {
        struct node {
            int64_t v, par, d;
        };
        stack<node> st;
        st.push(node{v, -1, 0});
        while (!st.empty()) {
            auto t = st.top();
            st.pop();
            depth[t.v] = t.d;
            parent[0][t.v] = t.par;
            for (auto i : data[t.v]) {
                if (i == t.par) continue;
                st.push(node{i, t.v, t.d + 1});
            }
        }
    }
    
    void build() {
        init(0);
        for (int64_t k = 0; k < logV - 1; ++k) {
			for (int64_t v = 0; v < V; ++v) {
				if (parent[k][v] < 0) parent[k + 1][v] = -1;
				else parent[k + 1][v] = parent[k][parent[k][v]];
			}
		}
	}

    void add_edge(int64_t a, int64_t b) {
        data[a].emplace_back(b);
        data[b].emplace_back(a);
    }
    
    int64_t lca(int64_t u, int64_t v) {
        if (depth[u] > depth[v]) swap(u, v);
		for (int64_t k = 0; k < logV; ++k) {
			if ((depth[v] - depth[u]) >> k & 1) v = parent[k][v];
		}
		if (u == v) return u;

		for (int64_t k = logV - 1; k >= 0; --k) {
			if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
		}
		return parent[0][u];
    }
};
