#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"
#include "graph/graph.hpp"
#include "template/atcoder.hpp"
#include "tree/undo_union_find.hpp"

struct S {
    int k, u, v;
};

int main(void) {
    sonic();
    int n, q;
    cin >> n >> q;
    Graph<pair<int, int>> g(q + 1);
    vector<vector<S>> querys(q + 1);
    rep(i, q) {
        int t, k, u, v;
        cin >> t >> k >> u >> v;
        if (t == 0) {
            g.add_edges(k + 1, i + 1, {u, v});
        } else {
            querys[k + 1].push_back({i + 1, u, v});
        }
    }

    undo_union_find uf(n);
    vector<int> ans(q + 1, -1);
    auto dfs = [&](auto self, int idx, int par) -> void {
        for (auto query : querys[idx]) {
            ans[query.k] = uf.same(query.u, query.v);
        }
        for (auto e : g[idx]) {
            if (e.to() == par)
                continue;
            bool flag = uf.unite(e.weight().first, e.weight().second);
            self(self, e.to(), idx);
            if (flag)
                uf.undo();
        }
    };

    dfs(dfs, 0, -1);

    rep(i, q + 1) {
        if (ans[i] != -1)
            co(ans[i]);
    }

    return 0;
}
