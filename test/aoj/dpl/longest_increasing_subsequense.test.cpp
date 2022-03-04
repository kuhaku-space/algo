#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/1/DPL_1_D"
#include "dp/lis.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    co(LIS(a));

    return 0;
}
