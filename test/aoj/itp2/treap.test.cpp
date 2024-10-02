// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ITP2_7_B
#include "binary_tree/treap.hpp"
#include <iostream>

int main(void) {
    int q;
    std::cin >> q;
    int size = 0;
    treap<int> tr;
    while (q--) {
        int x, y;
        std::cin >> x >> y;
        if (x == 0) {
            if (!tr.contains(y)) tr.insert(y), ++size;
            std::cout << size << '\n';
        } else if (x == 1) {
            std::cout << tr.contains(y) << '\n';
        } else if (x == 2) {
            if (tr.contains(y)) tr.erase(y), --size;
        }
    }

    return 0;
}
