#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum"
#include "template/atcoder.hpp"
#include "tree/link_cut_tree.hpp"

int main(void) {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;
    link_cut_tree<Add<ll>> lct(n);
    rep (i, n) {
        lct.set(i, a[i]);
    }
    rep (i, n - 1) {
        int u, v;
        cin >> u >> v;
        lct.link(u, v);
    }

    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int u, v, w, x;
            cin >> u >> v >> w >> x;
            lct.cut(u, v);
            lct.link(w, x);
        } else if (t == 1) {
            int p, x;
            cin >> p >> x;
            lct.set(p, lct.get_val(p) + x);
        } else if (t == 2) {
            int u, v;
            cin >> u >> v;
            lct.make_root(u);
            lct.expose(v);
            cout << lct.get_total(v) << endl;
        }
    }

    return 0;
}
