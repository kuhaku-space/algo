#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2995"
#include "tree/dynamic_union_find.hpp"
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include "graph/graph.hpp"
#include "tree/dsu_on_tree.hpp"

int main(void) {
    int n, k;
    std::cin >> n >> k;
    Graph<void> g(n);
    g.input_edges(n - 1);
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
    auto query_vertex = [&](int v) {
        auto [s, t] = a[v];
        duf.unite(s, t, f);
    };
    auto query_edge = [&](int u, int v) {};
    dsu.solve(rem, clear, query_vertex, query_edge);
    for (int i = 0; i < n; ++i) std::cout << ans[i] << '\n';

    return 0;
}
