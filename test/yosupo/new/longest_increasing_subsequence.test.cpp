#define PROBLEM "https://judge.yosupo.jp/problem/longest_increasing_subsequence"
#include "algorithm/lis.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    auto ans = make_lis(a);
    co(ans.size());
    co(ans);

    return 0;
}
