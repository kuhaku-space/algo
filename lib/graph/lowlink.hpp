#include "lib/template/template.hpp"
#include "graph/graph.hpp"

// verify : https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_A 21/02/26
// verify : https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_B 21/02/26

template <class T>
struct LowLink {
    const Graph<T> &g;
    vector<int> ord, low;
    vector<bool> used;
    vector<int> articulation;                // 関節点
    vector<typename Graph<T>::edge> bridge;  // 橋

    LowLink(const Graph<T> &_g)
        : g(_g), ord(_g.size()), low(_g.size()), used(_g.size()) {
        build();
    }

    int dfs(int idx, int k, int par) {
        used[idx] = true;
        ord[idx] = k++;
        low[idx] = ord[idx];
        bool is_articulation = false;
        int cnt = 0;
        for (auto &e : g[idx]) {
            if (!used[e.to]) {
                ++cnt;
                k = dfs(e.to, k, idx);
                chmin(low[idx], low[e.to]);
                is_articulation |= ~par && low[e.to] >= ord[idx];
                if (ord[idx] < low[e.to]) bridge.emplace_back(e);
            } else if (e.to != par) {
                chmin(low[idx], ord[e.to]);
            }
        }
        is_articulation |= par == -1 && cnt > 1;
        if (is_articulation) articulation.emplace_back(idx);
        return k;
    }

    void build() {
        int k = 0;
        for (int i = 0; i < g.size(); i++) {
            if (!used[i]) k = dfs(i, k, -1);
        }
    }

    auto get_articulation() { return articulation; }
    auto get_bridge() { return bridge; }
};
