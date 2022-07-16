#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_F"
#include "segment_tree/lazy_segment_tree.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, q;
    cin >> n >> q;
    lazy_segment_tree<Min<int>, Update<int>> st(n, std::numeric_limits<int>::max());
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
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
