#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_D"
#include "segment_tree/dual_segment_tree.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, q;
    cin >> n >> q;
    dual_segment_tree<Update<int>> st(n, (1LL << 31) - 1);
    rep(i, q) {
        int com;
        cin >> com;
        if (com == 0) {
            int s, t, x;
            cin >> s >> t >> x;
            st.apply(s, t + 1, x);
        } else {
            int x;
            cin >> x;
            co(st.get(x));
        }
    }

    return 0;
}
