#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include <iostream>
#include <utility>
#include <vector>
#include "binary_tree/fenwick_tree.hpp"
#include "graph/graph.hpp"
#include "tree/dsu_on_tree.hpp"
#include "tree/union_find.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    Graph<void> g(n);
    std::vector<int> a(n);
    for (int &x : a) std::cin >> x;
    for (int i = 0; i < n - 1; ++i) {
        int p;
        std::cin >> p;
        g.add_edge(p, i + 1);
    }
    std::vector<std::vector<std::pair<int, int>>> sol(n);
    std::vector<std::pair<int, int>> queries;
    int solve_count = 0;
    for (int i = 0; i < n; ++i) queries.emplace_back(i, a[i]);
    while (q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int u, x;
            std::cin >> u >> x;
            queries.emplace_back(u, x);
        } else {
            int u;
            std::cin >> u;
            sol[u].emplace_back(solve_count++, queries.size());
        }
    }
    std::vector<int> corr(queries.size());
    for (int i = 0; i < (int)queries.size(); ++i) { corr[i] = queries[i].first; }
    dsu_on_tree dsu(g, corr);
    std::vector<std::int64_t> ans(solve_count);
    fenwick_tree<std::int64_t> ft(queries.size());
    std::vector<std::pair<int, int>> history;
    auto rem = [&](int v) {
        for (auto &[u, x] : sol[v]) ans[u] = ft.sum(x);
    };
    auto clear = [&]() {
        for (auto [x, y] : history) ft.add(x, -y);
        history.clear();
    };
    auto query = [&](int i) {
        auto [x, y] = queries[i];
        ft.add(i, y);
        history.emplace_back(i, y);
    };
    dsu.solve(rem, clear, query);
    for (int i = 0; i < solve_count; ++i) std::cout << ans[i] << '\n';

    return 0;
}
