#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_D"
#include "binary_tree/fenwick_tree.hpp"
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

    HLD hld(g);
    fenwick_tree<ll> ft(n);
    int q;
    cin >> q;
    while (q--) {
        int id;
        std::cin >> id;
        if (id == 0) {
            int v, w;
            std::cin >> v >> w;
            auto f = [&](int a, int b) {
                ft.add(a, w);
            };
            hld.for_each_edge(hld.get_parent(v), v, f);
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
