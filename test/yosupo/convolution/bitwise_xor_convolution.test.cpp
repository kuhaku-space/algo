// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/bitwise_xor_convolution
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include "math/modint.hpp"

using Mint = modint998;

template <typename T>
void fwt(std::vector<T> &f) {
    int n = f.size();
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j++) {
            if ((j & i) == 0) {
                T x = f[j], y = f[j | i];
                f[j] = x + y, f[j | i] = x - y;
            }
        }
    }
}

template <typename T>
void ifwt(std::vector<T> &f) {
    int n = f.size();
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j++) {
            if ((j & i) == 0) {
                T x = f[j], y = f[j | i];
                f[j] = (x + y) / 2, f[j | i] = (x - y) / 2;
            }
        }
    }
}

int main(void) {
    int n;
    std::cin >> n;
    n = 1 << n;
    std::vector<Mint> a(n), b(n);
    std::copy_n(std::istream_iterator<Mint>(std::cin), n, std::begin(a));
    std::copy_n(std::istream_iterator<Mint>(std::cin), n, std::begin(b));
    fwt(a), fwt(b);
    std::vector<Mint> c(n);
    for (int i = 0; i < n; ++i) c[i] = a[i] * b[i];
    ifwt(c);
    for (int i = 0; i < n; ++i) std::cout << c[i] << (i == n - 1 ? '\n' : ' ');

    return 0;
}
