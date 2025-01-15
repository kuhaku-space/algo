// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2426
#include <iostream>
#include <vector>
#include "binary_tree/range_tree.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) std::cin >> x[i] >> y[i];
    range_tree<Add<int>> rt;
    for (int i = 0; i < n; ++i) rt.add(x[i], y[i]);
    rt.build();
    for (int i = 0; i < n; ++i) rt.set(x[i], y[i], rt.get(x[i], y[i]) + 1);
    for (int i = 0; i < m; ++i) {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        std::cout << rt.prod(a, b, c + 1, d + 1) << '\n';
    }

    return 0;
}
