// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/1276
#include <iostream>
#include "number_theory/prime_number.hpp"

Sieve<1300001> ls;

int main(void) {
    while (true) {
        int n;
        std::cin >> n;
        if (n == 0) break;
        int l = n, r = n;
        while (!ls.is_prime(l)) --l;
        while (!ls.is_prime(r)) ++r;
        std::cout << r - l << '\n';
    }

    return 0;
}
