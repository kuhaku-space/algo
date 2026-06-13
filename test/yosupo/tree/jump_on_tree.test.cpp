// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/jump_on_tree
#include <iostream>
#include "graph/edge_input.hpp"
#include "tree/hld.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    edge_input<void> ei(n - 1, 0);
    auto g = ei.to_undirected(n);
    heavy_light_decomposition hld(g);
    while (q--) {
        int u, v, k;
        std::cin >> u >> v >> k;
        std::cout << hld.jump(u, v, k) << '\n';
    }

    return 0;
}
