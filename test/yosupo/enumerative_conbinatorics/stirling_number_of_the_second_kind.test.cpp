// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind
#include <iostream>
#include "combinatorics/stirling1.hpp"

using Mint = modint998;

int main(void) {
    int n;
    std::cin >> n;
    auto ans = stirling2<Mint>(n);
    for (int i = 0; i <= n; ++i) std::cout << ans[i] << " \n"[i == n];

    return 0;
}
