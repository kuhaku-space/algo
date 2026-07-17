// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/CGL_4_A
#include "geometry/convex_hull.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

int main(void) {
    int n;
    std::cin >> n;
    std::vector<Point<int>> ps(n);
    for (auto &e : ps) std::cin >> e;
    auto v = convex_hull(ps);
    std::cout << v.size() << '\n';
    int t = 0;
    for (int i = 0; i < n; ++i) {
        if (v[i].y < v[t].y || (v[i].y == v[t].y && v[i].x < v[i].y)) t = i;
    }
    std::rotate(v.begin(), v.begin() + t, v.end());
    for (auto &[x, y] : v) std::cout << x << ' ' << y << '\n';

    return 0;
}
