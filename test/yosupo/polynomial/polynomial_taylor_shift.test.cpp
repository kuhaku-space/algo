// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/polynomial_taylor_shift
#include <iostream>
#include <vector>
#include "fft/formal_power_series.hpp"
#include "math/modint.hpp"

using Mint = modint998;

int main(void) {
    int n, c;
    std::cin >> n >> c;
    std::vector<Mint> a(n);
    for (auto &e : a) std::cin >> e;
    auto ans = fps::taylor_shift(a, Mint(c));
    for (int i = 0; i < n; ++i) std::cout << ans[i] << (i == n - 1 ? "\n" : " ");

    return 0;
}
