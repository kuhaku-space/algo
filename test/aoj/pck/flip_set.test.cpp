// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/0086
#include "data_structure/flip_set.hpp"
#include <iostream>

int main(void) {
    flip_set<int> fs;
    int a, b;
    while (std::cin >> a >> b) {
        if (a == 0 && b == 0) {
            std::cout << (fs.size() == 2 && fs.contains(1) && fs.contains(2) ? "OK" : "NG") << '\n';
            fs = flip_set<int>();
        } else {
            fs.flip(a);
            fs.flip(b);
        }
    }

    return 0;
}
