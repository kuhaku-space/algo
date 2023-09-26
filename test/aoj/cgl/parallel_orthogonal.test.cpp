#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/CGL_2_A"
#include "geometry/geometry.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int q;
    std::cin >> q;
    while (q--) {
        Point<double> a, b, c, d;
        std::cin >> a >> b >> c >> d;
        Line l(a, b), r(c, d);
        if (parallel(l, r)) co(2);
        else if (orthogonal(l, r)) co(1);
        else co(0);
    }

    return 0;
}
