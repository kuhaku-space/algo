// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ITP2_1_B
#include <iostream>
#include "data_structure/dynamic_sequence.hpp"
#include "segtree/monoid.hpp"

int main(void) {
    int q;
    std::cin >> q;
    dynamic_sequence<Add<int>> ds;
    while (q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int d, x;
            std::cin >> d >> x;
            if (d == 0) ds.push_front(x);
            else ds.push_back(x);
        } else if (t == 1) {
            int p;
            std::cin >> p;
            std::cout << ds.get(p) << '\n';
        } else {
            int d;
            std::cin >> d;
            if (d == 0) ds.pop_front();
            else ds.pop_back();
        }
    }

    return 0;
}
