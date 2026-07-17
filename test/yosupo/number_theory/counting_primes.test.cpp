// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/counting_primes
#include <iostream>
#include "math/prime_counting.hpp"

int main(void) {
    std::int64_t n;
    std::cin >> n;
    std::cout << prime_counting(n) << '\n';

    return 0;
}
