// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/static_range_inversions_query
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include "algorithm/compress.hpp"
#include "algorithm/mo.hpp"
#include "binary_tree/fenwick_tree.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    a = compress(a);
    std::int64_t sum = 0;
    int size = *max_element(a.begin(), a.end()) + 1;
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
        sum -= ft.sum(a[idx] + 1, size);
        ft.add(a[idx], -1);
    };
    Mo mo(n);
    mo.input(q, 0);
    mo.build();
    std::vector<std::int64_t> ans(q);
    while (q--) {
        int k = mo.process(fl, fr, gl, gr);
        ans[k] = sum;
    }
    for (auto x : ans) std::cout << x << '\n';

    return 0;
}
