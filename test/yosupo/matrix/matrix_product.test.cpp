#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"
#include "math/modint.hpp"
#include "matrix/matrix.hpp"
#include "template/atcoder.hpp"

using Mint = modint998;

int main(void) {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<Mint>> a(n, vector<Mint>(m)), b(m, vector<Mint>(k));
    cin >> a >> b;
    Matrix<Mint> x(a), y(b);
    auto z = x * y;
    for (auto v : z) co(v);

    return 0;
}
