#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"
#include "math/matrix.hpp"
#include "math/modint.hpp"
#include "template/atcoder.hpp"

using Mint = modint998;

int main(void) {
    int n;
    std::cin >> n;
    std::vector<std::vector<Mint>> v(n, std::vector<Mint>(n));
    std::cin >> v;
    Matrix mat(v);
    co(mat.det());

    return 0;
}
