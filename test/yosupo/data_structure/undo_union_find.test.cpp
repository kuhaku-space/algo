#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"
#include "tree/undo_union_find.hpp"
#include <iostream>
#include <utility>
#include <vector>
#include "graph/graph.hpp"

struct S {
    int k, u, v;
};

int main(void) {
    int n, q;
    std::cin >> n >> q;
    Graph<std::pair<int, int>> g(q + 1);
    std::vector<std::vector<S>> querys(q + 1);
    for (int i = 0; i < q; ++i) {
        int t, k, u, v;
        std::cin >> t >> k >> u >> v;
        if (t == 0) g.add_edges(k + 1, i + 1, {u, v});
        else querys[k + 1].emplace_back(i + 1, u, v);
    }

    undo_union_find uf(n);
    std::vector<int> ans(q + 1, -1);
    auto dfs = [&](auto self, int idx, int par) -> void {
        for (auto query : querys[idx]) ans[query.k] = uf.same(query.u, query.v);
        for (auto e : g[idx]) {
            if (e.to() == par) continue;
            bool flag = uf.unite(e.weight().first, e.weight().second);
            self(self, e.to(), idx);
            if (flag) uf.undo();
        }
    };
    dfs(dfs, 0, -1);
    for (int i = 0; i < q + 1; ++i) {
        if (ans[i] != -1) std::cout << ans[i] << '\n';
    }

    return 0;
}
