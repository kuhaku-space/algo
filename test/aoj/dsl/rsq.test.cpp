// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_B
#include <iostream>
#include "binary_tree/fenwick_tree.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    fenwick_tree<int> ft(n);
    while (q--) {
        int com, x, y;
        std::cin >> com >> x >> y;
        if (com == 0) ft.add(x - 1, y);
        else std::cout << ft.sum(x - 1, y) << '\n';
    }

    return 0;
}
