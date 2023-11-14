#define PROBLEM "https://judge.yosupo.jp/problem/addition_of_big_integers"
#include <iostream>
#include "data_structure/bigint.hpp"

int main(void) {
    int t;
    std::cin >> t;
    while (t--) {
        BigInt a, b;
        std::cin >> a >> b;
        std::cout << a + b << '\n';
    }

    return 0;
}
