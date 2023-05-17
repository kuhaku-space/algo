#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_D"
#include "algorithm/lis.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    co(longest_increasing_subsequence(a));

    return 0;
}
