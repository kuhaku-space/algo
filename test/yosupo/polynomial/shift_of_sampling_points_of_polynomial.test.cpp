// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial
#include <iostream>
#include <vector>
#include "convolution/formal_power_series.hpp"

using Mint = modint998;

int main(void) {
    int n, m, c;
    std::cin >> n >> m >> c;
    std::vector<Mint> y(n);
    for (auto &e : y) std::cin >> e;
    auto ans = fps::shift_of_sampling_points(y, Mint(c), m);
    for (int i = 0; i < m; ++i) std::cout << ans[i] << " \n"[i == m - 1];

    return 0;
}
