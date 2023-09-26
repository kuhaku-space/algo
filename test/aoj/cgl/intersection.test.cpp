#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/CGL_2_B"
#include "geometry/geometry.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int q;
    std::cin >> q;
    while (q--) {
        Point<double> a, b, c, d;
        std::cin >> a >> b >> c >> d;
        Line l(a, b), r(c, d);
        co(intersection(l, r));
    }

    return 0;
}
