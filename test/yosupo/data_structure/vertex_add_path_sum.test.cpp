#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include "binary_tree/fenwick_tree.hpp"
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
    fenwick_tree<ll> ft(n);
    rep (i, n) ft.add(hld.get(i), a[i]);
    while (q--) {
        int c;
        cin >> c;
        if (c == 0) {
            int p, x;
            cin >> p >> x;
            ft.add(hld.get(p), x);
        } else {
            int u, v;
            cin >> u >> v;
            ll ans = 0;
            auto f = [&](int u, int v) {
                ans += ft.sum(u, v);
            };
            hld.for_each(u, v, f);
            co(ans);
        }
    }

    return 0;
}
