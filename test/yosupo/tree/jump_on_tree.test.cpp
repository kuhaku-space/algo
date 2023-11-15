#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include <iostream>
#include "tree/hld.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    Graph<void> g(n);
    g.input_edges(n - 1, 0);
    heavy_light_decomposition hld(g);
    while (q--) {
        int u, v, k;
        std::cin >> u >> v >> k;
        std::cout << hld.jump(u, v, k) << '\n';
    }

    return 0;
}
