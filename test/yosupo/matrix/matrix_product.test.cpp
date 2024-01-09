#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"
#include <iostream>
#include <vector>
#include "math/matrix.hpp"
#include "math/modint.hpp"

using Mint = modint998;

int main(void) {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector a(n, std::vector(m, Mint())), b(m, std::vector(k, Mint()));
    for (auto &v : a) {
        for (auto &e : v) std::cin >> e;
    }
    for (auto &v : b) {
        for (auto &e : v) std::cin >> e;
    }
    Matrix<Mint> x(a), y(b);
    auto z = x * y;
    for (auto &&v : z) {
        for (int i = 0; i < (int)v.size(); ++i)
            std::cout << v[i] << (i == (int)v.size() - 1 ? '\n' : ' ');
    }

    return 0;
}
