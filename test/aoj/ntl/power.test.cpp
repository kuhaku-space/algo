#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_B"
#include "math/modint.hpp"
#include "template/atcoder.hpp"

using Mint = ModInt<MOD>;

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;
    co(Mint(n).pow(m));

    return 0;
}