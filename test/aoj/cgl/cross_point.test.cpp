#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/CGL_2_C"
#define ERROR 0.00000001
#include "geometry/geometry.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int q;
    std::cin >> q;
    while (q--) {
        Point<double> a, b, c, d;
        std::cin >> a >> b >> c >> d;
        Line l(a, b), m(c, d);
        co(cross_point(l, m));
    }

    return 0;
}
