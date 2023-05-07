#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_C"
#include "geometry/kdtree.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n;
    cin >> n;
    kdtree kd;
    rep (i, n) {
        int x, y;
        cin >> x >> y;
        kd.add(x, y);
    }
    kd.build();

    int q;
    cin >> q;
    rep (i, q) {
        int sx, tx, sy, ty;
        cin >> sx >> tx >> sy >> ty;
        auto v = kd.find(sx, tx + 1, sy, ty + 1);
        sort(all(v));
        for (auto i : v) co(i);
        cout << endl;
    }

    return 0;
}
