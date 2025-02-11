// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary
#include <iostream>
#include <vector>
#include "fft/monotone_minima.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n), b(m);
    for (auto &e : a) std::cin >> e;
    for (auto &e : b) std::cin >> e;
    auto ans = min_plus_convolution(b, a);
    for (int i = 0; i < (int)ans.size(); ++i)
        std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');

    return 0;
}
