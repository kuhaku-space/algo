// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1611
#include <cstdint>
#include <iostream>
#include <vector>
#include "math/factorize.hpp"

int main(void) {
    int t;
    std::cin >> t;
    std::vector<std::vector<std::uint64_t>> dp(32);
    for (int i = 2; i < 32; ++i) dp[i] = factorize(i);
    while (t--) {
        std::uint64_t x;
        std::cin >> x;
        auto v = factorize(x);
        auto c = number_of_divisors(v);
        for (int i = 0; i < 32; ++i) {
            auto u = dp[i];
            u.insert(u.end(), v.begin(), v.end());
            if (number_of_divisors(u) == c * 2) {
                std::cout << x * i << '\n';
                break;
            }
        }
    }
    return 0;
}
