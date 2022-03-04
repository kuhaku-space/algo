#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_C"
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
        auto ans = ccw(a, b, p);
        if (ans == 1)
            co("COUNTER_CLOCKWISE");
        else if (ans == -1)
            co("CLOCKWISE");
        else if (ans == 2)
            co("ONLINE_BACK");
        else if (ans == -2)
            co("ONLINE_FRONT");
        else
            co("ON_SEGMENT");
    }

    return 0;
}
