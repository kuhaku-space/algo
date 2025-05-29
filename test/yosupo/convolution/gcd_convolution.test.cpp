// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/gcd_convolution
#include <iostream>
#include <vector>
#include "math/eratosthenes.hpp"
#include "math/modint.hpp"

eratosthenes pn;
using Mint = modint998;

int main(void) {
    int n;
    std::cin >> n;
    std::vector<Mint> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 1; i <= n; ++i) std::cin >> b[i];
    for (int p = 2; p <= n; ++p) {
        if (!pn.is_prime(p)) continue;
        for (int i = n / p; i >= 1; --i) {
            a[i] += a[i * p];
            b[i] += b[i * p];
        }
    }
    for (int i = 1; i <= n; ++i) a[i] *= b[i];
    for (int p = 2; p <= n; ++p) {
        if (!pn.is_prime(p)) continue;
        for (int i = 1; i * p <= n; ++i) a[i] -= a[i * p];
    }
    for (int i = 1; i <= n; ++i) std::cout << a[i] << (i == n ? '\n' : ' ');

    return 0;
}
