// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2995
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include "graph/edge_input.hpp"
#include "tree/dsu_on_tree.hpp"
#include "union_find/dynamic_union_find.hpp"
#include "union_find/union_find.hpp"

// 固定サイズ union_find を使う版。
template <class G>
std::vector<int> solve_static(dsu_on_tree<G> &dsu, int n, int k, const std::vector<std::pair<int, int>> &a) {
    std::vector<int> ans(n);
    int sum = 0;
    union_find uf(k);
    std::vector<bool> flag(k);
    std::vector<int> history;
    auto rem = [&](int x) { ans[x] = sum; };
    auto clear = [&]() {
        sum = 0;
        for (int x : history) {
            uf[x] = -1;
            flag[x] = false;
        }
        history.clear();
    };
    auto f = [&](int x, int y) {
        if (x == y) {
            if (!flag[x]) {
                ++sum;
                flag[x] = true;
            }
        } else {
            if (!flag[x] || !flag[y]) ++sum;
            flag[x] = flag[x] | flag[y];
        }
    };
    auto query = [&](int v) {
        auto [s, t] = a[v];
        uf.unite(s, t, f);
        history.emplace_back(s);
        history.emplace_back(t);
    };
    dsu.solve(rem, clear, query);
    return ans;
}

// unordered_map ベースの動的 union_find を使う版。
template <class G>
std::vector<int> solve_dynamic(dsu_on_tree<G> &dsu, int n, const std::vector<std::pair<int, int>> &a) {
    std::vector<int> ans(n);
    int sum = 0;
    dynamic_union_find duf;
    std::unordered_map<int, bool> flag;
    auto rem = [&](int x) { ans[x] = sum; };
    auto clear = [&]() {
        sum = 0;
        duf.clear();
        flag.clear();
    };
    auto f = [&](int x, int y) {
        if (x == y) {
            if (!flag[x]) {
                ++sum;
                flag[x] = true;
            }
        } else {
            if (!flag[x] || !flag[y]) ++sum;
            flag[x] |= flag[y];
        }
    };
    auto query = [&](int v) {
        auto [s, t] = a[v];
        duf.unite(s, t, f);
    };
    dsu.solve(rem, clear, query);
    return ans;
}

int main(void) {
    int n, k;
    std::cin >> n >> k;
    edge_input<void> ei(n - 1);
    auto g = ei.to_undirected(n);
    dsu_on_tree dsu(g);
    std::vector<std::pair<int, int>> a(n);
    for (auto &[x, y] : a) std::cin >> x >> y, --x, --y;

    auto ans_static = solve_static(dsu, n, k, a);
    auto ans_dynamic = solve_dynamic(dsu, n, a);
    assert(ans_static == ans_dynamic);
    for (int i = 0; i < n; ++i) std::cout << ans_static[i] << '\n';

    return 0;
}
