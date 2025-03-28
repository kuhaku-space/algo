// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/vertex_set_path_composite
#include <iostream>
#include <utility>
#include <vector>
#include "math/modint.hpp"
#include "segtree/segment_tree.hpp"
#include "tree/hld.hpp"

using Mint = modint998;
using M = Affine<Mint>;
using RM = Rev<M>;

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<std::pair<Mint, Mint>> a(n);
    for (auto &[x, y] : a) std::cin >> x >> y;
    Graph<void> g(n);
    g.input_edges(n - 1, 0);
    heavy_light_decomposition hld(g);
    segment_tree<M> st1(n);
    segment_tree<RM> st2(n);
    for (int i = 0; i < n; ++i) {
        st1.set(hld.get(i), a[i]);
        st2.set(hld.get(i), a[i]);
    }

    while (q--) {
        int c;
        std::cin >> c;
        if (c == 0) {
            int p, a, b;
            std::cin >> p >> a >> b;
            st1.set(hld.get(p), {a, b});
            st2.set(hld.get(p), {a, b});
        } else {
            int u, v, x;
            std::cin >> u >> v >> x;
            auto l = M::id(), r = M::id();
            auto f = [&](int u, int v) { l = M::op(st1.prod(u, v), l); };
            auto g = [&](int u, int v) { r = RM::op(st2.prod(u, v), r); };
            int lca = hld.lca(u, v);
            hld.for_each(lca, u, f);
            hld.for_each_edge(lca, v, g);
            auto ans = RM::op(l, r);
            std::cout << (ans.first * x + ans.second) << '\n';
        }
    }

    return 0;
}
