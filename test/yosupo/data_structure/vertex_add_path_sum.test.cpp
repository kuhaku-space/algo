#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include "binary_tree/BIT.hpp"
#include "template/atcoder.hpp"
#include "tree/hld.hpp"

int main(void) {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;
    HLD hld(n);
    hld.input_edges(0);
    hld.build();
    BIT<ll> bt(n);
    rep (i, n) bt.add(hld.get(i), a[i]);
    while (q--) {
        int c;
        cin >> c;
        if (c == 0) {
            int p, x;
            cin >> p >> x;
            bt.add(hld.get(p), x);
        } else {
            int u, v;
            cin >> u >> v;
            ll ans = 0;
            auto f = [&](int u, int v) {
                ans += bt.sum(u, v);
            };
            hld.for_each(u, v, f);
            co(ans);
        }
    }

    return 0;
}
