// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2995
#include "tree/dsu_on_tree.hpp"
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include "data_structure/union_find.hpp"
#include "graph/edge_input.hpp"

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
    for (int i = 0; i < n; ++i) std::cout << ans[i] << '\n';

    return 0;
}
