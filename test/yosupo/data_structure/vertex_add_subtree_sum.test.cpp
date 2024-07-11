// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/vertex_add_subtree_sum
#include <cstdint>
#include <iostream>
#include <vector>
#include "segment_tree/segment_tree.hpp"
#include "tree/eular_tour.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n), p(n - 1);
    for (auto &e : a) std::cin >> e;
    for (auto &e : p) std::cin >> e;
    Graph<void> g(n);
    for (int i = 0; i < n - 1; ++i) g.add_edges(i + 1, p[i]);
    eular_tour et(g);
    segment_tree<Add<std::int64_t>> st(n);
    for (int i = 0; i < n; ++i) st.set(et.get_l(i), a[i]);

    while (q--) {
        int c;
        std::cin >> c;
        if (c == 0) {
            int v, x;
            std::cin >> v >> x;
            st.set(et.get_l(v), st.get(et.get_l(v)) + x);
        } else {
            int v;
            std::cin >> v;
            auto f = [&](int l, int r) { std::cout << st.prod(l, r) << '\n'; };
            et.query(v, f);
        }
    }

    return 0;
}
