#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_A"
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
        Line l(a, b), r(c, d);
        if (parallel(l, r)) co(2);
        else if (orthogonal(l,r))
            co(1);
        else
            co(0);
    }

    return 0;
}
