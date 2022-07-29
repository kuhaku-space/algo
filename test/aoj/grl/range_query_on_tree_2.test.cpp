#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/5/GRL_5_E"
#include "binary_tree/fenwick_tree_raq.hpp"
#include "template/atcoder.hpp"
#include "tree/hld.hpp"

int main(void) {
    int n;
    cin >> n;
    fenwick_tree_raq<ll> ft(n);
    HLD hld(n);
    rep (i, n) {
        int k;
        cin >> k;
        rep (j, k) {
            int c;
            cin >> c;
            hld.add_edge(i, c);
        }
    }
    hld.build();

    int q;
    cin >> q;
    while (q--) {
        int id;
        cin >> id;
        if (id == 0) {
            int v, w;
            cin >> v >> w;
            auto f = [&](int a, int b) {
                ft.add(a, b, w);
            };
            hld.for_each_edge(0, v, f);
        } else {
            int v;
            cin >> v;
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
