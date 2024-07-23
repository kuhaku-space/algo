// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_A
#include <iostream>
#include "math/prime_number.hpp"

prime_number pn;

int main(void) {
    int n;
    std::cin >> n;
    auto v = pn.prime_factorization(n);
    std::cout << n << ':';
    for (auto p : v) {
        for (int i = 0; i < p.second; ++i) std::cout << ' ' << p.first;
    }
    std::cout << '\n';

    return 0;
}
