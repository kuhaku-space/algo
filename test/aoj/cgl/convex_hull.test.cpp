// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/CGL_4_A
#include "geometry/convex_hull.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main(void) {
    int n;
    std::cin >> n;
    std::vector<Point<int>> ps(n);
    std::copy_n(std::istream_iterator<Point<int>>(std::cin), n, std::begin(ps));
    auto v = convex_hull(ps);
    std::cout << std::size(v) << '\n';

    int t = 0;
    for (int i = 0; i < n; ++i) {
        if (v[i].y < v[t].y || (v[i].y == v[t].y && v[i].x < v[i].y)) t = i;
    }

    std::rotate(std::begin(v), std::begin(v) + t, std::end(v));
    for (auto &[x, y] : v) std::cout << x << ' ' << y << '\n';

    return 0;
}
