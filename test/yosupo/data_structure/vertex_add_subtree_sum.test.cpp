// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/vertex_add_subtree_sum
#include <cstdint>
#include <iostream>
#include <vector>
#include "segtree/segment_tree.hpp"
#include "tree/euler_tour.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n), p(n - 1);
    for (auto &e : a) std::cin >> e;
    for (auto &e : p) std::cin >> e;
    Graph<void> g(n);
    for (int i = 0; i < n - 1; ++i) g.add_edges(i + 1, p[i]);
    euler_tour et(g);
    segment_tree<Add<std::int64_t>> st(n);
    for (int i = 0; i < n; ++i) st.set(et.left(i), a[i]);

    while (q--) {
        int c;
        std::cin >> c;
        if (c == 0) {
            int v, x;
            std::cin >> v >> x;
            st.set(et.left(v), st.get(et.left(v)) + x);
        } else {
            int v;
            std::cin >> v;
            auto [l, r] = et[v];
            std::cout << st.prod(l, r) << '\n';
        }
    }

    return 0;
}
