#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_1_A"
#include "tree/union_find.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    union_find uf(n);
    while (q--) {
        int com, x, y;
        std::cin >> com >> x >> y;
        if (com == 0) uf.unite(x, y);
        else co(uf.same(x, y));
    }

    return 0;
}
