#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DPL_5_I"
#include "math/enumeration.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, k;
    cin >> n >> k;
    Enumeration<modint107> enume;
    co(enume.stirling(n, k));

    return 0;
}
