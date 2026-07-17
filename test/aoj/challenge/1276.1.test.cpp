// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/1276
#include <iostream>
#include "math/eratosthenes.hpp"

eratosthenes<1300000> pr;

int main(void) {
    while (true) {
        int n;
        std::cin >> n;
        if (n == 0) break;
        int l = n, r = n;
        while (!pr.is_prime(l)) --l;
        while (!pr.is_prime(r)) ++r;
        std::cout << r - l << '\n';
    }

    return 0;
}
