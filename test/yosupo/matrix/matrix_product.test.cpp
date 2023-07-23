#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"
#include "math/matrix.hpp"
#include "math/modint.hpp"
#include "template/atcoder.hpp"

using Mint = modint998;

int main(void) {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector a(n, std::vector(m, Mint())), b(m, std::vector(k, Mint()));
    std::cin >> a >> b;
    Matrix<Mint> x(a), y(b);
    auto z = x * y;
    for (auto v : z) co(v);

    return 0;
}
