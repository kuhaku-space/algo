// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_B
#include <iostream>
#include "number_theory/bigint.hpp"

int main(void) {
    BigInt a, b;
    std::cin >> a >> b;
    std::cout << a - b << '\n';

    return 0;
}
