#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/5/GRL_5_E"
#include "binary_tree/BIT_RAQ.hpp"
#include "template/atcoder.hpp"
#include "tree/hld.hpp"

int main(void) {
    int n;
    cin >> n;
    BIT_RAQ<ll> bit(n);
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
    rep (i, q) {
        int id;
        cin >> id;
        if (id == 0) {
            int v, w;
            cin >> v >> w;
            auto f = [&](int a, int b) {
                bit.add(a, b, w);
            };
            hld.for_each_edge(0, v, f);
        } else {
            int v;
            cin >> v;
            ll ans = 0;
            auto f = [&](int a, int b) {
                ans += bit.sum(a, b);
            };
            hld.for_each_edge(0, v, f);
            co(ans);
        }
    }

    return 0;
}
