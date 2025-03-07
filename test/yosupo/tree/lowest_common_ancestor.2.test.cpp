// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/lca
#include <iostream>
#include <vector>
#include "graph/graph.hpp"
#include "tree/linear_lca.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> p(n - 1);
    for (auto &e : p) std::cin >> e;
    Graph<void> g(n);
    for (int i = 0; i < n - 1; ++i) g.add_edges(p[i], i + 1);
    linear_lca tr(g);
    while (q--) {
        int u, v;
        std::cin >> u >> v;
        std::cout << tr.lca(u, v) << '\n';
    }

    return 0;
}
