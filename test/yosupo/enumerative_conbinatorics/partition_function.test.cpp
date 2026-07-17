// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/partition_function
#include "math/partition_function.hpp"
#include <iostream>

using Mint = modint998;

int main(void) {
    int n;
    std::cin >> n;
    auto ans = partition_function<Mint>(n);
    for (int i = 0; i <= n; ++i) std::cout << ans[i] << " \n"[i == n];

    return 0;
}
