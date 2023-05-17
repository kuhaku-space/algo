#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_B"
#include "math/modint.hpp"
#include "template/atcoder.hpp"

using Mint = modint107;

int main(void) {
    int n, m;
    cin >> n >> m;
    co(Mint(n).pow(m));

    return 0;
}
