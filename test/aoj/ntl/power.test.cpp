// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_B
#include <iostream>
#include "math/modint.hpp"

using Mint = modint107;

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::cout << Mint(n).pow(m) << std::endl;

    return 0;
}
