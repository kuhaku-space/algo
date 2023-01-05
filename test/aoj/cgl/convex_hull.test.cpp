#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/CGL_4_A"
#include "geometry/convex_hull.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n;
    cin >> n;
    vector<Point<ll>> ps(n);
    cin >> ps;
    auto v = convex_hull(ps);
    co(v.size());

    int t = 0;
    rep (i, n) {
        if (v[i].y < v[t].y || (v[i].y == v[t].y && v[i].x < v[i].y)) t = i;
    }

    rotate(v.begin(), v.begin() + t, v.end());
    for (auto &[x, y] : v) co(x, y);

    return 0;
}
