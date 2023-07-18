#define PROBLEM "https://judge.yosupo.jp/problem/longest_increasing_subsequence"
#include "algorithm/lis.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n;
    std::cin >> n;
    vector<int> a(n);
    std::cin >> a;

    auto ans = make_lis(a);
    co(ans.size());
    co(ans);

    return 0;
}
