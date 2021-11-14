#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    cin >> a;
    a.emplace_back(0);
    repr(i, n) a[i] += a[i + 1];
    rep(i, q) {
        int l, r;
        cin >> l >> r;
        co(a[l] - a[r]);
    }

    return 0;
}
