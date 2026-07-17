// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/843
#include <iostream>
#include "math/eratosthenes.hpp"

eratosthenes<500000> pr;

int main(void) {
    int n;
    std::cin >> n;
    if (n == 1) {
        std::cout << 0 << '\n';
        return 0;
    }
    int ans = 1;
    for (int i = 3; i <= n && i * i - 2 <= n; ++i) {
        if (pr.is_prime(i) && pr.is_prime(i * i - 2)) ans += 2;
    }
    std::cout << ans << '\n';

    return 0;
}
