// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind_small_p_large_n
#include <cstdint>
#include <iostream>
#include "combinatorics/stirling_small_p_large_n.hpp"

int main(void) {
    int t;
    unsigned p;
    std::cin >> t >> p;
    StirlingSmallPLargeN calc(p);
    while (t--) {
        std::int64_t n, k;
        std::cin >> n >> k;
        std::cout << calc.stirling1(n, k) << '\n';
    }

    return 0;
}
