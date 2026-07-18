// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/kth_root_mod
#include <iostream>
#include "math/modint.hpp"
#include "number_theory/root_mod.hpp"

int main(void) {
    int t;
    std::cin >> t;
    while (t--) {
        long long k, y, p;
        std::cin >> k >> y >> p;
        modint::set_mod((int)p);
        modint x(y);
        if (auto r = kth_root_mod(x, k)) std::cout << *r << '\n';
        else std::cout << -1 << '\n';
    }

    return 0;
}
