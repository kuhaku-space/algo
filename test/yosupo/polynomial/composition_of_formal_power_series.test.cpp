// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/composition_of_formal_power_series
#include <iostream>
#include <vector>
#include "convolution/formal_power_series.hpp"

using Mint = modint998;

int main(void) {
    int n;
    std::cin >> n;
    std::vector<Mint> a(n), b(n);
    for (auto &e : a) std::cin >> e;
    for (auto &e : b) std::cin >> e;
    auto ans = fps::composition(a, b, n);
    for (int i = 0; i < n; ++i) std::cout << ans[i] << " \n"[i == n - 1];

    return 0;
}
