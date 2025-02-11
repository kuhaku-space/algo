// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/subset_convolution
#include "fft/subset_convolution.hpp"
#include <iostream>
#include <vector>
#include "math/modint.hpp"

using Mint = modint998;

int main(void) {
    int n;
    std::cin >> n;
    std::vector<Mint> a(1 << n), b(1 << n);
    for (auto &e : a) std::cin >> e;
    for (auto &e : b) std::cin >> e;
    auto ans = subset_convolution(a, b);
    for (int i = 0; i < (int)ans.size(); ++i)
        std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');

    return 0;
}
