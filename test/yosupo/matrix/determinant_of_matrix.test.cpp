#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"
#include <iostream>
#include <vector>
#include "math/matrix.hpp"
#include "math/modint.hpp"

using Mint = modint998;

int main(void) {
    int n;
    std::cin >> n;
    std::vector<std::vector<Mint>> v(n, std::vector<Mint>(n));
    for (auto &u : v) {
        for (auto &e : u) std::cin >> e;
    }
    Matrix mat(v);
    std::cout << mat.det() << '\n';

    return 0;
}
