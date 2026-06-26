// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/polynomial_interpolation
#include <iostream>
#include <vector>
#include "convolution/formal_power_series.hpp"

using Mint = modint998;

int main(void) {
    int n;
    std::cin >> n;
    std::vector<Mint> x(n), y(n);
    for (Mint &e : x) std::cin >> e;
    for (Mint &e : y) std::cin >> e;
    auto ans = fps::polynomial_interpolation(x, y);
    for (int i = 0; i < n; ++i) std::cout << ans[i] << " \n"[i == n - 1];

    return 0;
}
