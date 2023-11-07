#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_G"
#include <cstdint>
#include <iostream>
#include "binary_tree/fenwick_tree_raq.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    fenwick_tree_raq<std::int64_t> ft(n);
    while (q--) {
        int com;
        std::cin >> com;
        if (com == 0) {
            int s, t, x;
            std::cin >> s >> t >> x;
            ft.add(s - 1, t, x);
        } else {
            int s, t;
            std::cin >> s >> t;
            std::cout << ft.sum(s - 1, t) << std::endl;
        }
    }

    return 0;
}
