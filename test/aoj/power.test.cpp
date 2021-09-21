#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_B"
#include "algo/modint.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n,m;
    cin >> n >> m;
    co(Mint(n).pow(m));

    return 0;
}
