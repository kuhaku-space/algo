// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2995
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include "graph/edge_input.hpp"
#include "tree/dsu_on_tree.hpp"
#include "union_find/dynamic_union_find.hpp"

int main(void) {
    int n, k;
    std::cin >> n >> k;
    edge_input<void> ei(n - 1);
    auto g = ei.to_undirected(n);
    dsu_on_tree dsu(g);
    std::vector<std::pair<int, int>> a(n);
    for (auto &[x, y] : a) std::cin >> x >> y, --x, --y;
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
    for (int i = 0; i < n; ++i) std::cout << ans[i] << '\n';

    return 0;
}
