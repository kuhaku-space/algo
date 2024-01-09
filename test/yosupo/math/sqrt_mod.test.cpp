#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"
#include <iostream>
#include "math/modint.hpp"
#include "math/sqrt.hpp"

int main(void) {
    int t;
    std::cin >> t;
    while (t--) {
        int y, p;
        std::cin >> y >> p;
        modint::set_mod(p);
        modint x(y);
        if (has_sqrt_mod(x)) std::cout << sqrt_mod(x) << '\n';
        else std::cout << -1 << '\n';
    }

    return 0;
}
