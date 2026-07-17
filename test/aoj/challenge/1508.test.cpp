// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/1508
#include <iostream>
#include "data_structure/dynamic_sequence.hpp"
#include "segtree/monoid.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    dynamic_sequence<Min<int>> ds;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        ds.push_back(x);
    }
    while (q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int l, r;
            std::cin >> l >> r, ++r;
            if (l + 1 == r) continue;
            auto [lp, mp, rp] = ds.split(l, r);
            auto [lm, rm] = mp.split(r - l - 1);
            rm.merge_right(lm);
            lp.merge_right(rm);
            lp.merge_right(rp);
            ds = lp;
        } else if (t == 1) {
            int l, r;
            std::cin >> l >> r, ++r;
            std::cout << ds.prod(l, r) << '\n';
        } else {
            int k, x;
            std::cin >> k >> x;
            ds.set(k, x);
        }
    }

    return 0;
}
