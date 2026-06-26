// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/sqrt_of_formal_power_series
#include <cstdint>
#include <iostream>
#include <vector>
#include "convolution/formal_power_series.hpp"

using Mint = modint998;

int main(void) {
    int n;
    std::cin >> n;
    std::vector<Mint> a(n);
    for (auto &e : a) std::cin >> e;
    auto ans = fps::sqrt(a);
    if (ans.empty()) {
        std::cout << -1 << '\n';
        return 0;
    }
    for (int i = 0; i < n; ++i) std::cout << ans[i] << " \n"[i == n - 1];

    return 0;
}
