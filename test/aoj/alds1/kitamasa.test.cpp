// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_10_A
#include <cstdint>
#include <iostream>
#include <vector>
#include "math/linear_recurrence.hpp"

int main(void) {
    int n;
    std::cin >> n;
    std::vector<std::int64_t> a(2, 1), d(2, 1);
    std::cout << kitamasa(a, d, n) << '\n';

    return 0;
}
