#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1/DSL_1_B"
#include "template/atcoder.hpp"
#include "tree/weighted_union_find.hpp"

int main(void) {
    sonic();
    int n, q;
    cin >> n >> q;

    weighted_union_find<int> uf(n);
    while (q--) {
        int com;
        cin >> com;
        if (com == 0) {
            int x, y, w;
            cin >> x >> y >> w;
            uf.unite(x, y, w);
        } else {
            int x, y;
            cin >> x >> y;
            if (uf.same(x, y)) {
                co(uf.diff(x, y));
            } else {
                co('?');
            }
        }
    }

    return 0;
}
