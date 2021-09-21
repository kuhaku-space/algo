#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/5/ALDS1_5_D"
#include "binary_tree/BIT.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    vector<pair<int, int>> b(n);
    rep(i, n) b[i] = {a[i], i};
    sort(all(b));
    BIT<int> bit(n);
    ll ans = 0;
    repr(i, n) {
        ans += bit.sum(b[i].second);
        bit.add(b[i].second, 1);
    }
    co(ans);

    return 0;
}
