// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/lca
#include <cassert>
#include <iostream>
#include <vector>
#include "graph/edge_input.hpp"
#include "tree/hld.hpp"
#include "tree/linear_lca.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> p(n - 1);
    for (auto &e : p) std::cin >> e;
    edge_input<void> ei;
    for (int i = 0; i < n - 1; ++i) ei.emplace(p[i], i + 1);
    auto g = ei.to_undirected(n);

    heavy_light_decomposition hld(g);
    linear_lca tr(g);
    while (q--) {
        int u, v;
        std::cin >> u >> v;
        int ans = hld.lca(u, v);
        assert(ans == tr.lca(u, v));
        std::cout << ans << '\n';
    }

    return 0;
}
