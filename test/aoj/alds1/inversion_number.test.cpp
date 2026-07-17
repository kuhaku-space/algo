// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_5_D
#include "algorithm/inversion_number.hpp"
#include <iostream>
#include <vector>

int main(void) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    std::cout << inversion_number(a) << '\n';

    return 0;
}
