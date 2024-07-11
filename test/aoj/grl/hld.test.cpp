// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_C
#include "tree/hld.hpp"
#include <iostream>

int main(void) {
    int n;
    std::cin >> n;
    Graph<void> g(n);
    for (int i = 0; i < n; ++i) {
        int k;
        std::cin >> k;
        while (k--) {
            int c;
            std::cin >> c;
            g.add_edges(i, c);
        }
    }

    heavy_light_decomposition hld(g);
    int q;
    std::cin >> q;
    while (q--) {
        int u, v;
        std::cin >> u >> v;
        std::cout << hld.lca(u, v) << std::endl;
    }

    return 0;
}
