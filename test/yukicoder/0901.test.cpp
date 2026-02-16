// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/901
#include <cstdint>
#include <iostream>
#include <vector>
#include "graph/graph.hpp"
#include "segtree/segment_tree.hpp"
#include "tree/auxiliary_tree.hpp"
#include "tree/hld.hpp"

int main(void) {
    int n;
    std::cin >> n;
    Graph<std::int64_t> g(n);
    g.input_edges(n - 1, 0);
    heavy_light_decomposition hld(g);
    segment_tree<Add<std::int64_t>> st(n);
    auto f = [&](auto self, int x, int p) -> void {
        for (auto e : g[x]) {
            if (e.to() == p) continue;
            st.set(hld.get(e.to()), e.weight());
            self(self, e.to(), x);
        }
    };
    f(f, 0, -1);

    auxiliary_tree_builder at(g);
    int q;
    std::cin >> q;
    while (q--) {
        int k;
        std::cin >> k;
        std::vector<int> x(k);
        for (auto &e : x) std::cin >> e;
        auto tr = at.build(x);
        std::int64_t ans = 0;
        auto g = [&](int x, int y) { ans += st.prod(x, y); };
        auto dfs = [&](auto self, int v, int p) -> void {
            for (auto e : tr[v]) {
                if (e.to() == p) continue;
                hld.for_each_edge(tr.vertex(v), tr.vertex(e.to()), g);
                self(self, e.to(), v);
            }
        };
        dfs(dfs, 0, -1);
        std::cout << ans << '\n';
    }

    return 0;
}
