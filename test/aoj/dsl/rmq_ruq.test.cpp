// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_F
#include <iostream>
#include <limits>
#include "segment_tree/lazy_segment_tree.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    lazy_segment_tree<Min<int>, Update<int>> st(n, std::numeric_limits<int>::max());
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
