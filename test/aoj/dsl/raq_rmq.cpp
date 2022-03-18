#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H"
#include "segment_tree/segment_tree_raq.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, q;
    cin >> n >> q;
    segment_tree_range_add_range_min<ll> st(n, 0);

    rep(i, q) {
        int type;
        cin >> type;
        if (type == 0) {
            int s, t, x;
            cin >> s >> t >> x;
            st.apply(s, t + 1, x);
        } else {
            int s, t;
            cin >> s >> t;
            co(st.prod(s, t + 1));
        }
    }

    return 0;
}
