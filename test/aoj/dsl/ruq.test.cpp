#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_D"
#include "segment_tree/dual_segment_tree.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    dual_segment_tree<Update<int>> st(n, (1LL << 31) - 1);
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
            co(st.get(x));
        }
    }

    return 0;
}
