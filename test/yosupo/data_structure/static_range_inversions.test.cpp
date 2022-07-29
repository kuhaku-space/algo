#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"
#include "algorithm/compress.hpp"
#include "algorithm/mo.hpp"
#include "binary_tree/fenwick_tree.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;
    a = compress(a);
    ll sum = 0;
    int size = *max_element(all(a)) + 1;
    fenwick_tree<int> ft(size);
    auto fl = [&](int idx) {
        sum += ft.sum(a[idx]);
        ft.add(a[idx], 1);
    };
    auto fr = [&](int idx) {
        sum += ft.sum(a[idx] + 1, size);
        ft.add(a[idx], 1);
    };
    auto gl = [&](int idx) {
        sum -= ft.sum(a[idx]);
        ft.add(a[idx], -1);
    };
    auto gr = [&](int idx) {
        sum -= ft.sum(a[idx] - 1, size);
        ft.add(a[idx], -1);
    };
    Mo mo(n, fl, fr, gl, gr);
    mo.input(q, 0);
    mo.build();
    vector<ll> ans(q);
    while (q--) {
        int k = mo.process();
        ans[k] = sum;
    }
    for (auto x : ans) co(x);

    return 0;
}
