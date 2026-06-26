// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/primitive_root
#include <cstdint>
#include <iostream>
#include "number_theory/factorize.hpp"

int main(void) {
    int q;
    std::cin >> q;
    while (q--) {
        std::uint64_t p;
        std::cin >> p;
        std::cout << primitive_root(p) << '\n';
    }

    return 0;
}
