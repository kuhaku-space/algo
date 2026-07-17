// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DPL_5_G
#include <iostream>
#include "math/enumeration.hpp"

int main(void) {
    int n, k;
    std::cin >> n >> k;
    Enumeration<modint107> enume;
    std::cout << enume.bell(n, k) << '\n';

    return 0;
}
