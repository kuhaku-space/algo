// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_mod_1000000007
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include "fft/ntt_mod.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n), b(m);
    std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(a));
    std::copy_n(std::istream_iterator<int>(std::cin), m, std::begin(b));
    auto ans = convolution_mod<modint107::mod()>(a, b);
    for (int i = 0; i < (int)ans.size(); ++i)
        std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');

    return 0;
}
