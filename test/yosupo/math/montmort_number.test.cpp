#define PROBLEM "https://judge.yosupo.jp/problem/montmort_number_mod"
#include "template/atcoder.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    ll sum = 0;
    std::vector<int> ans(n);
    rep (i, n) {
        ans[i] = sum;
        sum *= i + 2;
        if (i & 1) sum += m - 1;
        else ++sum;
        sum %= m;
    }
    co(ans);

    return 0;
}
