#define PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series"
#include <iostream>
#include <vector>
#include "fft/formal_power_series.hpp"

using Mint = modint998;

int main(void) {
    int n;
    std::cin >> n;
    std::vector<Mint> a(n);
    for (auto &e : a) std::cin >> e;
    auto ans = fps::log(a);
    for (int i = 0; i < (int)ans.size(); ++i)
        std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');

    return 0;
}
