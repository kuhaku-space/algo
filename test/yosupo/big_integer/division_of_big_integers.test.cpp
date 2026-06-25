// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/division_of_big_integers
#include <iostream>
#include "math/bigint.hpp"

int main(void) {
    int t;
    std::cin >> t;
    while (t--) {
        BigInt a, b;
        std::cin >> a >> b;
        auto [q, r] = a.div_mod(b);
        std::cout << q << ' ' << r << '\n';
    }

    return 0;
}
