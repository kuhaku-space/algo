#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_1_C"
#include <iostream>
#include "math/prime_number.hpp"

prime_number pn;

int main(void) {
    int n;
    std::cin >> n;
    int ans = 0;
    while (n--) {
        int a;
        std::cin >> a;
        ans += pn.is_prime(a);
    }
    std::cout << ans << std::endl;

    return 0;
}
