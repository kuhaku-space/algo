// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/sqrt_mod
#include <iostream>
#include "math/modint.hpp"
#include "number_theory/root_mod.hpp"

int main(void) {
    int t;
    std::cin >> t;
    while (t--) {
        int y, p;
        std::cin >> y >> p;
        modint::set_mod(p);
        modint x(y);
        if (auto r = sqrt_mod(x)) std::cout << *r << '\n';
        else std::cout << -1 << '\n';
    }

    return 0;
}
