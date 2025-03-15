// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_A
#include <iostream>
#include <limits>
#include "segtree/segment_tree_raq.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    segment_tree_range_add_range_min<int> st(n, std::numeric_limits<int>::max());
    while (q--) {
        int com, x, y;
        std::cin >> com >> x >> y;
        if (com == 0) st.set(x, y);
        else std::cout << st.prod(x, y + 1) << '\n';
    }

    return 0;
}
