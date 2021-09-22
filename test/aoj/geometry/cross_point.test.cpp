#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_C"
#include "geometry/geometry.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    setp(10);
    int q;
    cin >> q;
    while (q--) {
        Point<double> a, b, c, d;
        cin >> a >> b >> c >> d;
        Line l(a, b), m(c, d);
        co(cross_point(l, m));
    }

    return 0;
}
