// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DPL_5_I
#include <iostream>
#include "combinatorics/stirling_bell.hpp"

int main(void) {
    int n, k;
    std::cin >> n >> k;
    StirlingBell<modint107> enume;
    std::cout << enume.stirling(n, k) << '\n';

    return 0;
}
