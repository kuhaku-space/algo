#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"
#include <iostream>
#include <vector>
#include "fft/formal_power_series.hpp"

using Mint = modint998;

int main(void) {
    int n;
    std::cin >> n;
    std::vector<Mint> x(n), y(n);
    for (Mint &e : x) std::cin >> e;
    for (Mint &e : y) std::cin >> e;
    auto ans = fps::polynomial_interpolation(x, y);
    for (int i = 0; i < (int)ans.size(); ++i) {
        std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');
    }

    return 0;
}
