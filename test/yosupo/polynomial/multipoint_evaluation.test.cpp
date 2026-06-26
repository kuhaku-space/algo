// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/multipoint_evaluation
#include <iostream>
#include <vector>
#include "convolution/formal_power_series.hpp"

using Mint = modint998;

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::vector<Mint> c(n), p(m);
    for (Mint &e : c) std::cin >> e;
    for (Mint &e : p) std::cin >> e;
    auto ans = fps::multipoint_evaluation(c, p);
    for (int i = 0; i < m; ++i) std::cout << ans[i] << " \n"[i == m - 1];

    return 0;
}
