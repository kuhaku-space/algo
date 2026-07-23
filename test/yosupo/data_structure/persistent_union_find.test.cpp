// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/persistent_unionfind
#include <cassert>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include "graph/graph.hpp"
#include "union_find/persistent_union_find.hpp"
#include "union_find/undo_union_find.hpp"

// 真の永続配列で、クエリを与えられた順のままオンラインに処理する版。
std::vector<bool> solve_persistent(int n, const std::vector<std::tuple<int, int, int, int>> &queries) {
    std::vector<persistent_union_find> ufs;
    ufs.emplace_back(n);
    std::vector<bool> ans;
    for (auto &[t, k, u, v] : queries) {
        if (t == 0) {
            ufs.emplace_back(ufs[k + 1].unite(u, v));
        } else {
            ans.emplace_back(ufs[k + 1].same(u, v));
            ufs.emplace_back();
        }
    }
    return ans;
}

// クエリ列からバージョン木を構築し、undo 可能 union find で木を DFS するオフライン版。
// 木上で頂点 idx を訪れた時点の union find の状態が「バージョン idx」に対応する。
std::vector<bool> solve_undo(int n, int q, const std::vector<std::tuple<int, int, int, int>> &queries) {
    struct PendingQuery {
        int ans_idx, u, v;
    };
    list_graph<std::pair<int, int>> g(q + 1);
    std::vector<std::vector<PendingQuery>> pending(q + 1);
    for (int i = 0; i < q; ++i) {
        auto &[t, k, u, v] = queries[i];
        if (t == 0) g.add_edges(k + 1, i + 1, {u, v});
        else pending[k + 1].emplace_back(PendingQuery{i + 1, u, v});
    }

    undo_union_find uf(n);
    std::vector<int> ans(q + 1, -1);
    auto dfs = [&](auto self, int idx, int par) -> void {
        for (auto &pq : pending[idx]) ans[pq.ans_idx] = uf.same(pq.u, pq.v);
        for (auto e : g[idx]) {
            if (e.to() == par) continue;
            bool flag = uf.unite(e.weight().first, e.weight().second);
            self(self, e.to(), idx);
            if (flag) uf.undo();
        }
    };
    dfs(dfs, 0, -1);

    std::vector<bool> res;
    for (int i = 0; i < q + 1; ++i) {
        if (ans[i] != -1) res.emplace_back(ans[i]);
    }
    return res;
}

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<std::tuple<int, int, int, int>> queries(q);
    for (auto &[t, k, u, v] : queries) std::cin >> t >> k >> u >> v;

    auto ans_persistent = solve_persistent(n, queries);
    auto ans_undo = solve_undo(n, q, queries);
    assert(ans_persistent == ans_undo);
    for (bool x : ans_persistent) std::cout << x << '\n';

    return 0;
}
