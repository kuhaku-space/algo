// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/bell_number
#include <iostream>
#include "math/bell.hpp"

using Mint = modint998;

int main(void) {
    int n;
    std::cin >> n;
    auto ans = bell<Mint>(n);
    for (int i = 0; i <= n; ++i) std::cout << ans[i] << (i == n ? '\n' : ' ');

    return 0;
}
