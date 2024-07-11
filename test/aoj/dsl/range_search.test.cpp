// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_C
#include <algorithm>
#include <iostream>
#include "geometry/kdtree.hpp"

int main(void) {
    int n;
    std::cin >> n;
    kdtree kd;
    while (n--) {
        int x, y;
        std::cin >> x >> y;
        kd.add(x, y);
    }
    kd.build();

    int q;
    std::cin >> q;
    while (q--) {
        int sx, tx, sy, ty;
        std::cin >> sx >> tx >> sy >> ty;
        auto v = kd.find(sx, tx + 1, sy, ty + 1);
        std::sort(v.begin(), v.end());
        for (auto e : v) std::cout << e << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
