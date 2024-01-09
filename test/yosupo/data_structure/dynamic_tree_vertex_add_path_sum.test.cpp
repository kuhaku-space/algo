#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <vector>
#include "tree/link_cut_tree.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    link_cut_tree<Add<std::int64_t>> lct(n);
    for (int i = 0; i < n; ++i) lct.set(i, a[i]);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        lct.link(u, v);
    }

    while (q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int u, v, w, x;
            std::cin >> u >> v >> w >> x;
            lct.cut(u, v);
            lct.link(w, x);
        } else if (t == 1) {
            int p, x;
            std::cin >> p >> x;
            lct.set(p, lct.get_val(p) + x);
        } else if (t == 2) {
            int u, v;
            std::cin >> u >> v;
            lct.make_root(u);
            lct.expose(v);
            std::cout << lct.get_total(v) << '\n';
        }
    }

    return 0;
}
