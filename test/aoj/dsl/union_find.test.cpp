#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1/DSL_1_A"
#include "template/atcoder.hpp"
#include "tree/union_find.hpp"

int main(void) {
    sonic();
    int n, q;
    cin >> n >> q;

    union_find uf(n);
    while (q--) {
        int com, x, y;
        cin >> com >> x >> y;
        if (com == 0) {
            uf.unite(x, y);
        } else {
            co(uf.same(x, y));
        }
    }

    return 0;
}
