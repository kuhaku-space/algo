// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/find_linear_recurrence
#include <iostream>
#include <vector>
#include "math/berlekamp_massey.hpp"
#include "math/modint.hpp"

using Mint = modint998;

int main() {
    int n;
    std::cin >> n;
    std::vector<Mint> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    auto c = berlekamp_massey(a);
    const int d = c.size();
    std::cout << d << '\n';
    for (int i = 0; i < d; ++i) std::cout << c[i] << " \n"[i + 1 == d];
    if (d == 0) std::cout << '\n';
    return 0;
}
