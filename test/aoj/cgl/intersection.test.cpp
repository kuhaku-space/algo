#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/CGL_2_B"
#include <iostream>
#include "geometry/geometry.hpp"

int main(void) {
    int q;
    std::cin >> q;
    while (q--) {
        Point<double> a, b, c, d;
        std::cin >> a >> b >> c >> d;
        Line l(a, b), r(c, d);
        std::cout << intersection(l, r) << std::endl;
    }

    return 0;
}
