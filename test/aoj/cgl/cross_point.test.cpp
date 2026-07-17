// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/CGL_2_C
// competitive-verifier: ERROR 0.00000001
#include <iostream>
#include "geometry/geometry.hpp"
#include "template/sonic.hpp"

int main(void) {
    int q;
    std::cin >> q;
    while (q--) {
        Point<double> a, b, c, d;
        std::cin >> a >> b >> c >> d;
        Line l(a, b), m(c, d);
        std::cout << cross_point(l, m) << '\n';
    }

    return 0;
}
