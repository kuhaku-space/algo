#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_C"
#include "tree/hld.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n;
    std::cin >> n;
    Graph<void> g(n);
    rep (i, n) {
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
        co(hld.lca(u, v));
    }

    return 0;
}
