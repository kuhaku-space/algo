// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1028
#include <iostream>
#include <vector>
#include "math/slope_trick.hpp"

int main(void) {
    int n;
    std::cin >> n;
    std::vector a(n, std::vector(n, 0));
    for (auto &v : a) {
        for (auto &e : v) std::cin >> e;
    }
    std::vector<slope_trick<int>> v(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            v[a[i][j] - 1].add_const(j);
            v[a[i][j] - 1].add_x_minus_a(i + j);
            v[a[i][j] - 1].add_a_minus_x(i - j);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) ans += v[i].min_value();
    std::cout << ans << '\n';

    return 0;
}
