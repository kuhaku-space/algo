// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_mod
#include <iostream>
#include <vector>
#include "fft/ntt.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n), b(m);
    for (auto &e : a) std::cin >> e;
    for (auto &e : b) std::cin >> e;
    auto ans = convolution(a, b);
    for (int i = 0; i < (int)ans.size(); ++i) std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');

    return 0;
}
