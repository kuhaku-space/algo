// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/843
#include <iostream>
#include "number_theory/prime_number.hpp"

Sieve<500000> sieve;

int main(void) {
    int n;
    std::cin >> n;
    if (n == 1) {
        std::cout << 0 << '\n';
        return 0;
    }
    int ans = 1;
    for (int i = 3; i <= n && i * i - 2 <= n; ++i) {
        if (sieve.is_prime(i) && sieve.is_prime(i * i - 2)) ans += 2;
    }
    std::cout << ans << '\n';

    return 0;
}
