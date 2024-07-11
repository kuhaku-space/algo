// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DSL_1_B
#include "tree/weighted_union_find.hpp"
#include <iostream>

int main(void) {
    int n, q;
    std::cin >> n >> q;
    weighted_union_find<int> uf(n);
    while (q--) {
        int com;
        std::cin >> com;
        if (com == 0) {
            int x, y, w;
            std::cin >> x >> y >> w;
            uf.unite(x, y, w);
        } else {
            int x, y;
            std::cin >> x >> y;
            if (uf.same(x, y)) std::cout << uf.diff(x, y) << std::endl;
            else std::cout << '?' << std::endl;
        }
    }

    return 0;
}
