// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2426
#include <cassert>
#include <iostream>
#include <vector>
#include "algorithm/compress.hpp"
#include "algorithm/cumulative_sum.hpp"
#include "data_structure/range_tree.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) std::cin >> x[i] >> y[i];

    // 2 次元 range tree をオンラインに使う版。
    range_tree<Add<int>> rt;
    for (int i = 0; i < n; ++i) rt.add(x[i], y[i]);
    rt.build();
    for (int i = 0; i < n; ++i) rt.set(x[i], y[i], rt.get(x[i], y[i]) + 1);

    // 座標圧縮 + 2 次元累積和でオフラインに前計算する版。
    coordinate_compression<int> cps_x, cps_y;
    for (int i = 0; i < n; ++i) cps_x.add(x[i]), cps_y.add(y[i]);
    cps_x.build(), cps_y.build();
    cumulative_sum_2d<int> cs(cps_x.size(), cps_y.size());
    for (int i = 0; i < n; ++i) cs.add(cps_x.get(x[i]), cps_y.get(y[i]), 1);
    cs.build();

    for (int i = 0; i < m; ++i) {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        int ans_rt = rt.prod(a, b, c + 1, d + 1);
        int ans_cs = cs.get(cps_x.get(a), cps_y.get(b), cps_x.get(c + 1), cps_y.get(d + 1));
        assert(ans_rt == ans_cs);
        std::cout << ans_rt << '\n';
    }

    return 0;
}
