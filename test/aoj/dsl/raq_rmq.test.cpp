// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_H
#include <cstdint>
#include <iostream>
#include "segtree/segment_tree_raq.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    segment_tree_range_add_range_min<std::int64_t> st(n, 0);
    while (q--) {
        int com;
        std::cin >> com;
        if (com == 0) {
            int s, t, x;
            std::cin >> s >> t >> x;
            st.apply(s, t + 1, x);
        } else {
            int s, t;
            std::cin >> s >> t;
            std::cout << st.prod(s, t + 1) << '\n';
        }
    }

    return 0;
}
