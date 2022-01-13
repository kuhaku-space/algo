#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C"
#include "template/atcoder.hpp"
#include "tree/hld.hpp"

int main(void) {
    sonic();
    int n;
    cin >> n;
    HLD hld(n);
    rep(i, n) {
        int k;
        cin >> k;
        rep(j, k) {
            int c;
            cin >> c;
            hld.add_edge(i, c);
        }
    }

    hld.build();

    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        co(hld.lca(u, v));
    }

    return 0;
}
