// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/0009
#include <iostream>
#include "algorithm/prefix_sum.hpp"
#include "math/eratosthenes.hpp"

eratosthenes<1000000> pr;

int main(void) {
    int n = 1000000;
    std::vector<int> v(n);
    for (int i = 2; i < n; ++i) v[i] = pr.is_prime(i);
    prefix_sum<int> ps(v);
    int x;
    while (std::cin >> x) std::cout << ps.sum(x + 1) << std::endl;

    return 0;
}
