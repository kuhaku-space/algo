// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_B
#include <iostream>
#include "fenwick/fenwick_tree.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    FenwickTree<int> ft(n);
    while (q--) {
        int com, x, y;
        std::cin >> com >> x >> y;
        if (com == 0) ft.add(x - 1, y);
        else std::cout << ft.sum(x - 1, y) << '\n';
    }

    return 0;
}
