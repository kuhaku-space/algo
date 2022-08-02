#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"
#include "data_structure/li_chao_tree.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, q;
    cin >> n >> q;
    li_chao_tree lct(-Inf, Inf);
    while (n--) {
        ll l, r, a, b;
        cin >> l >> r >> a >> b;
        lct.add_segment(a, b, l, r);
    }
    while (q--) {
        int c;
        cin >> c;
        if (c == 0) {
            ll l, r, a, b;
            cin >> l >> r >> a >> b;
            lct.add_segment(a, b, l, r);
        } else {
            ll x;
            cin >> x;
            auto ans = lct.query(x);
            if (ans == li_chao_tree::inf) co("INFINITY");
            else co(ans);
        }
    }

    return 0;
}
