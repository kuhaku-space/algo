// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/vertex_add_subtree_sum
#include <cassert>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include "data_structure/fenwick_tree.hpp"
#include "graph/edge_input.hpp"
#include "segtree/segment_tree.hpp"
#include "tree/dsu_on_tree.hpp"
#include "tree/euler_tour.hpp"
#include "union_find/union_find.hpp"

// オイラーツアー + セグメント木でオンラインに処理する版。
std::vector<std::int64_t> solve_euler_tour(int n, const std::vector<int> &a, const std::vector<int> &p,
                                           const std::vector<std::tuple<int, int, int>> &ops) {
    edge_input<void> ei;
    for (int i = 0; i < n - 1; ++i) ei.emplace(i + 1, p[i]);
    auto g = ei.to_undirected(n);
    euler_tour et(g);
    segment_tree<Add<std::int64_t>> st(n);
    for (int i = 0; i < n; ++i) st.set(et.left(i), a[i]);

    std::vector<std::int64_t> ans;
    for (auto &[c, v, x] : ops) {
        if (c == 0) {
            st.set(et.left(v), st.get(et.left(v)) + x);
        } else {
            auto [l, r] = et[v];
            ans.emplace_back(st.prod(l, r));
        }
    }
    return ans;
}

// dsu on tree + フェニック木でオフラインに処理する版。
std::vector<std::int64_t> solve_dsu_on_tree(int n, const std::vector<int> &a, const std::vector<int> &p,
                                            const std::vector<std::tuple<int, int, int>> &ops) {
    edge_input<void> ei;
    for (int i = 0; i < n - 1; ++i) ei.emplace(p[i], i + 1);
    auto g = ei.to_directed(n);
    std::vector<std::vector<std::pair<int, int>>> sol(n);
    std::vector<std::pair<int, int>> queries;
    int solve_count = 0;
    for (int i = 0; i < n; ++i) queries.emplace_back(i, a[i]);
    for (auto &[c, v, x] : ops) {
        if (c == 0) {
            queries.emplace_back(v, x);
        } else {
            sol[v].emplace_back(solve_count++, queries.size());
        }
    }
    std::vector<int> corr(queries.size());
    for (int i = 0; i < (int)queries.size(); ++i) corr[i] = queries[i].first;
    dsu_on_tree dsu(g, corr);
    std::vector<std::int64_t> ans(solve_count);
    FenwickTree<std::int64_t> ft(queries.size());
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
    return ans;
}

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n), p(n - 1);
    for (auto &e : a) std::cin >> e;
    for (auto &e : p) std::cin >> e;

    std::vector<std::tuple<int, int, int>> ops(q);
    for (auto &[c, v, x] : ops) {
        std::cin >> c;
        if (c == 0) std::cin >> v >> x;
        else std::cin >> v;
    }

    auto ans_euler_tour = solve_euler_tour(n, a, p, ops);
    auto ans_dsu_on_tree = solve_dsu_on_tree(n, a, p, ops);
    assert(ans_euler_tour == ans_dsu_on_tree);
    for (auto x : ans_euler_tour) std::cout << x << '\n';

    return 0;
}
