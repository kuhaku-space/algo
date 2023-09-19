#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include "binary_tree/fenwick_tree.hpp"
#include "template/atcoder.hpp"
#include "tree/hld.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    std::cin >> a;
    Graph<void> g(n);
    g.input_edges(n - 1, 0);
    HLD hld(g);
    fenwick_tree<ll> ft(n);
    rep (i, n) ft.add(hld.get(i), a[i]);
    while (q--) {
        int c;
        std::cin >> c;
        if (c == 0) {
            int p, x;
            std::cin >> p >> x;
            ft.add(hld.get(p), x);
        } else {
            int u, v;
            std::cin >> u >> v;
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
