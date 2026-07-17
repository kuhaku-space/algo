// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_A
#include <iostream>
#include <limits>
#include "segtree/lazy_segment_tree.hpp"
#include "segtree/monoid.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    lazy_segment_tree<Min<int>, Add<int>> st(n, std::numeric_limits<int>::max());
    while (q--) {
        int com, x, y;
        std::cin >> com >> x >> y;
        if (com == 0) st.set(x, y);
        else std::cout << st.prod(x, y + 1) << '\n';
    }

    return 0;
}
