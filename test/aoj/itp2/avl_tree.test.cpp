// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ITP2_7_B
#include "binary_tree/avl_tree.hpp"
#include <iostream>

int main(void) {
    int q;
    std::cin >> q;
    int size = 0;
    avl_tree<int> at;
    while (q--) {
        int x, y;
        std::cin >> x >> y;
        if (x == 0) {
            if (!at.contains(y)) at.insert(y), ++size;
            std::cout << size << std::endl;
        } else if (x == 1) {
            std::cout << at.contains(y) << std::endl;
        } else if (x == 2) {
            if (at.contains(y)) at.erase(y), --size;
        }
    }

    return 0;
}
