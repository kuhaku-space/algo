// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_1_C
#include <iostream>
#include "number_theory/prime_number.hpp"

Sieve<100000001> sieve;

int main(void) {
    int n;
    std::cin >> n;
    int ans = 0;
    while (n--) {
        int a;
        std::cin >> a;
        ans += sieve.is_prime(a);
    }
    std::cout << ans << '\n';

    return 0;
}
