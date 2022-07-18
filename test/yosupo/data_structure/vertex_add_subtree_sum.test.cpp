#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include "segment_tree/segment_tree.hpp"
#include "template/atcoder.hpp"
#include "tree/eular_tour.hpp"

int main(void) {
    int n, q;
    cin >> n >> q;
    vector<int> a(n), p(n - 1);
    cin >> a >> p;
    Graph<void> g(n);
    rep (i, n - 1) {
        g.add_edges(i + 1, p[i]);
    }
    eular_tour et(g);
    segment_tree<Add<ll>> st(n);
    rep (i, n) st.set(et.get_l(i), a[i]);
    while (q--) {
        int c;
        cin >> c;
        if (c == 0) {
            int v, x;
            cin >> v >> x;
            st.set(et.get_l(v), st.get(et.get_l(v)) + x);
        } else {
            int v;
            cin >> v;
            auto f = [&](int l, int r) {
                co(st.prod(l, r));
            };
            et.query(v, f);
        }
    }

    return 0;
}
