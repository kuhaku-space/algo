#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"
#include "data_structure/li_chao_tree.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, q;
    cin >> n >> q;
    li_chao_tree lct(-Inf, Inf);
    while (n--) {
        ll a, b;
        cin >> a >> b;
        lct.add_line(a, b);
    }
    while (q--) {
        int c;
        cin >> c;
        if (c == 0) {
            ll a, b;
            cin >> a >> b;
            lct.add_line(a, b);
        } else {
            ll x;
            cin >> x;
            co(lct.query(x));
        }
    }

    return 0;
}
