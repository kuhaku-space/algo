#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_E"
#include "binary_tree/fenwick_tree_raq.hpp"
#include "template/atcoder.hpp"
#include "tree/hld.hpp"

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
    fenwick_tree_raq<ll> ft(n);
    int q;
    std::cin >> q;
    while (q--) {
        int id;
        std::cin >> id;
        if (id == 0) {
            int v, w;
            std::cin >> v >> w;
            auto f = [&](int a, int b) {
                ft.add(a, b, w);
            };
            hld.for_each_edge(0, v, f);
        } else {
            int v;
            std::cin >> v;
            ll ans = 0;
            auto f = [&](int a, int b) {
                ans += ft.sum(a, b);
            };
            hld.for_each_edge(0, v, f);
            co(ans);
        }
    }

    return 0;
}
