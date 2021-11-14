#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_I"
#include "math/enumeration.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, k;
    cin >> n >> k;
    Enumeration<MOD> enume;
    co(enume.stirling(n, k));

    return 0;
}
