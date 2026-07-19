// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind_fixed_k
#include <iostream>
#include "combinatorics/stirling.hpp"

using Mint = modint998;

int main(void) {
    int n, k;
    std::cin >> n >> k;
    auto ans = stirling1_fixed_k<Mint>(n, k);
    for (int i = k; i <= n; ++i) std::cout << ans[i] << " \n"[i == n];

    return 0;
}
