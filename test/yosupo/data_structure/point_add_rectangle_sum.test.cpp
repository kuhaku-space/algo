#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"
#include "binary_tree/range_tree.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, q;
    cin >> n >> q;
    range_tree<Add<ll>> rt;
    vector<tuple<int, int, int>> points(n);
    for (auto &[x, y, z] : points) {
        cin >> x >> y >> z;
        rt.add(x, y);
    }
    vector<tuple<int, int, int, int, int>> queries(q);
    for (auto &[x, y, z, w, v] : queries) {
        cin >> x;
        cin >> y >> z >> w;
        if (x == 1) cin >> v;
        if (x == 0) rt.add(y, z);
    }

    rt.build();
    for (auto [x, y, z] : points) rt.set(x, y, rt.get(x, y) + z);
    for (auto [x, y, z, w, v] : queries) {
        if (x == 0) rt.set(y, z, rt.get(y, z) + w);
        else co(rt.prod(y, z, w, v));
    }

    return 0;
}
