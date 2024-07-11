// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DPL_5_I
#include <iostream>
#include "math/enumeration.hpp"

int main(void) {
    int n, k;
    std::cin >> n >> k;
    Enumeration<modint107> enume;
    std::cout << enume.stirling(n, k) << std::endl;

    return 0;
}
