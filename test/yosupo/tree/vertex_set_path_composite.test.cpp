// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/vertex_set_path_composite
#include <iostream>
#include <vector>
#include "math/modint.hpp"
#include "segtree/monoid.hpp"
#include "tree/segment_tree_on_tree.hpp"

using Mint = modint998;
using M = Affine<Mint>;

int main(void) {
    int n, q;
    std::cin >> n >> q;
    segment_tree_on_tree<M> st(n);
    std::vector<std::pair<Mint, Mint>> p(n);
    for (int i = 0; i < n; ++i) std::cin >> p[i].first >> p[i].second;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        st.add_edge(u, v);
    }
    st.build(p);
    while (q--) {
        int c;
        std::cin >> c;
        if (c == 0) {
            int p, a, b;
            std::cin >> p >> a >> b;
            st.set_vertex(p, {a, b});
        } else {
            int u, v, x;
            std::cin >> u >> v >> x;
            auto ans = st.prod(u, v);
            std::cout << (ans.first * x + ans.second) << '\n';
        }
    }

    return 0;
}
