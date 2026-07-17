// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/CGL_1_A
// competitive-verifier: ERROR 0.00000001
#include <iostream>
#include "geometry/geometry.hpp"
#include "template/sonic.hpp"

int main(void) {
    Point<double> a, b;
    std::cin >> a >> b;
    Line l(a, b);
    int q;
    std::cin >> q;
    while (q--) {
        Point<double> p;
        std::cin >> p;
        auto ans = l.proj(p);
        std::cout << ans << '\n';
    }

    return 0;
}
