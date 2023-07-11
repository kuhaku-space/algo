#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_B"
#include "binary_tree/fenwick_tree.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, q;
    cin >> n >> q;
    fenwick_tree<int> ft(n);
    while (q--) {
        int com, x, y;
        cin >> com >> x >> y;
        if (com == 0) ft.add(x - 1, y);
        else co(ft.sum(x - 1, y));
    }

    return 0;
}
