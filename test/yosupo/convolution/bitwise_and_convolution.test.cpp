#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"
#include "math/modint.hpp"
#include "template/atcoder.hpp"

using Mint = modint998;

template <typename T>
void fwt(vector<T> &f) {
    int n = f.size();
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j++) {
            if ((j & i) == 0) {
                f[j] += f[j | i];
            }
        }
    }
}
template <typename T>
void ifwt(vector<T> &f) {
    int n = f.size();
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j++) {
            if ((j & i) == 0) {
                f[j] -= f[j | i];
            }
        }
    }
}

int main(void) {
    int n;
    std::cin >> n;
    n = 1 << n;
    std::vector<Mint> a(n), b(n);
    std::cin >> a >> b;
    fwt(a), fwt(b);
    std::vector<Mint> c(n);
    rep (i, n) c[i] = a[i] * b[i];
    ifwt(c);
    co(c);

    return 0;
}
