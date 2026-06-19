// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/vertex_add_subtree_sum
#include <iostream>
#include <utility>
#include <vector>
#include "binary_tree/fenwick_tree.hpp"
#include "data_structure/union_find.hpp"
#include "graph/edge_input.hpp"
#include "tree/dsu_on_tree.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int &x : a) std::cin >> x;
    edge_input<void> ei;
    for (int i = 0; i < n - 1; ++i) {
        int p;
        std::cin >> p;
        ei.emplace(p, i + 1);
    }
    auto g = ei.to_directed(n);
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
