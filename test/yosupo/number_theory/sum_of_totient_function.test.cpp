// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/sum_of_totient_function
#include <iostream>
#include "math/modint.hpp"
#include "number_theory/multiplicative_function.hpp"

using Mint = modint998;

int main() {
    long long n;
    std::cin >> n;
    std::cout << totient_sum<Mint>(n) << '\n';
    return 0;
}
