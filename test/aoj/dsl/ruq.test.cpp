// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_D
#include <iostream>
#include <limits>
#include "segment_tree/dual_segment_tree.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    dual_segment_tree<Update<int>> st(n, std::numeric_limits<int>::max());
    while (q--) {
        int com;
        std::cin >> com;
        if (com == 0) {
            int s, t, x;
            std::cin >> s >> t >> x;
            st.apply(s, t + 1, x);
        } else {
            int x;
            std::cin >> x;
            std::cout << st.get(x) << std::endl;
        }
    }

    return 0;
}
