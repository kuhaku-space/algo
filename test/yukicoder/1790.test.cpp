// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1790
#include <cstdint>
#include <iostream>
#include <tuple>
#include <vector>
#include "graph/graph.hpp"
#include "tree/euler_tour_tree.hpp"

int main(void) {
    int n;
    std::cin >> n;
    std::vector<std::tuple<int, int, std::int64_t>> edge(n - 1);
    for (auto &[u, v, x] : edge) {
        std::cin >> u >> v >> x;
        --u, --v;
    }

    Graph<void> g(2 * n - 1);
    std::vector<std::int64_t> a(2 * n - 1);
    for (int i = 0; i < n - 1; ++i) {
        auto [u, v, x] = edge[i];
        g.add_edges(u, n + i);
        g.add_edges(v, n + i);
        a[n + i] = x;
    }
    std::vector<int> par(2 * n - 1, -1);
    auto dfs = [&](auto self, int x, int p) -> void {
        par[x] = p;
        for (auto e : g[x]) {
            if (e.to() == p) continue;
            self(self, e.to(), x);
        }
    };
    dfs(dfs, 0, -1);

    euler_tour_tree<Xor<std::int64_t>> et(a);
    for (int i = 0; i < n - 1; ++i) {
        auto [u, v, x] = edge[i];
        et.link(u, n + i);
        et.link(v, n + i);
    }

    int q;
    std::cin >> q;
    while (q--) {
        int t, x;
        std::cin >> t >> x;
        --x;
        if (t == 1) {
            if (et.same(x, 0)) et.cut(par[x], par[par[x]]);
        } else {
            if (!et.same(x, 0)) std::cout << 0 << '\n';
            else std::cout << et.get_subtree(x, par[x]) << '\n';
        }
    }

    return 0;
}
