// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/vertex_add_path_sum
#include <cstdint>
#include <iostream>
#include <vector>
#include "binary_tree/fenwick_tree.hpp"
#include "tree/hld.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    Graph<void> g(n);
    g.input_edges(n - 1, 0);
    heavy_light_decomposition hld(g);
    fenwick_tree<std::int64_t> ft(n);
    for (int i = 0; i < n; ++i) ft.add(hld.get(i), a[i]);

    while (q--) {
        int c;
        std::cin >> c;
        if (c == 0) {
            int p, x;
            std::cin >> p >> x;
            ft.add(hld.get(p), x);
        } else {
            int u, v;
            std::cin >> u >> v;
            std::int64_t ans = 0;
            auto f = [&](int u, int v) { ans += ft.sum(u, v); };
            hld.for_each(u, v, f);
            std::cout << ans << '\n';
        }
    }

    return 0;
}
