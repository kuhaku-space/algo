// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DSL_5_B
#include <algorithm>
#include <iostream>
#include "algorithm/prefix_sum_2d.hpp"

int main(void) {
    constexpr int size = 1000;  // 座標の上限
    int n;
    std::cin >> n;
    PrefixSum2D<int, true> ps(size, size);
    while (n--) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        ps.add(x1, y1, x2, y2, 1);
    }
    ps.build();

    int ans = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) ans = std::max(ans, ps.get(i, j));
    }
    std::cout << ans << '\n';

    return 0;
}
