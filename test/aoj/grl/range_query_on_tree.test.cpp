#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_D"
#include <cstdint>
#include <iostream>
#include "binary_tree/fenwick_tree.hpp"
#include "tree/hld.hpp"

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
    fenwick_tree<std::int64_t> ft(n);
    int q;
    std::cin >> q;
    while (q--) {
        int id;
        std::cin >> id;
        if (id == 0) {
            int v, w;
            std::cin >> v >> w;
            auto f = [&](int a, int b) { ft.add(a, w); };
            hld.for_each_edge(hld.get_parent(v), v, f);
        } else {
            int v;
            std::cin >> v;
            std::int64_t ans = 0;
            auto f = [&](int a, int b) { ans += ft.sum(a, b); };
            hld.for_each_edge(0, v, f);
            std::cout << ans << std::endl;
        }
    }

    return 0;
}
