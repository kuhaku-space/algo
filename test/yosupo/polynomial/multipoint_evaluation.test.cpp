// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/multipoint_evaluation
#include <iostream>
#include <vector>
#include "fft/formal_power_series.hpp"

using Mint = modint998;

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::vector<Mint> c(n), p(m);
    for (Mint &e : c) std::cin >> e;
    for (Mint &e : p) std::cin >> e;
    auto ans = fps::multipoint_evaluation(c, p);
    for (int i = 0; i < (int)ans.size(); ++i) {
        std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');
    }

    return 0;
}
