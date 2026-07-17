// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2426
#include <iostream>
#include <utility>
#include <vector>
#include "algorithm/compress.hpp"
#include "algorithm/cumulative_sum.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i].first >> a[i].second;
    coordinate_compression<int> cps_x, cps_y;
    for (int i = 0; i < n; ++i) cps_x.add(a[i].first), cps_y.add(a[i].second);
    cps_x.build(), cps_y.build();
    cumulative_sum_2d<int> cs(cps_x.size(), cps_y.size());
    for (int i = 0; i < n; ++i) cs.add(cps_x.get(a[i].first), cps_y.get(a[i].second), 1);
    cs.build();
    for (int i = 0; i < m; ++i) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        std::cout << cs.get(cps_x.get(x1), cps_y.get(y1), cps_x.get(x2 + 1), cps_y.get(y2 + 1))
                  << '\n';
    }

    return 0;
}
