#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/CGL_1_C"
#include <cstdio>
#include <iostream>
#include "geometry/geometry.hpp"

int main(void) {
    Point<double> a, b;
    std::cin >> a >> b;
    Line l(a, b);
    int q;
    std::cin >> q;
    while (q--) {
        Point<double> p;
        std::cin >> p;
        auto ans = ccw(a, b, p);
        if (ans == 1) std::puts("COUNTER_CLOCKWISE");
        else if (ans == -1) std::puts("CLOCKWISE");
        else if (ans == 2) std::puts("ONLINE_BACK");
        else if (ans == -2) std::puts("ONLINE_FRONT");
        else std::puts("ON_SEGMENT");
    }

    return 0;
}
