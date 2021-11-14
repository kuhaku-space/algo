#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_A"
#define ERROR 0.00000001
#include "geometry/geometry.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    setp(10);
    Point<double> a, b;
    cin >> a >> b;
    Line l(a, b);
    int q;
    cin >> q;
    while (q--) {
        Point<double> p;
        cin >> p;
        auto ans = l.proj(p);
        co(ans);
    }

    return 0;
}
