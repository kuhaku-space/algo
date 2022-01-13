#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"
#include "template/atcoder.hpp"
#include "segment_tree/segment_tree.hpp"

int main(void) {
    sonic();
    int n, q;
    cin >> n >> q;
    segment_tree<Min<int>, Update<int>> st(n, (1LL << 31) - 1);
    rep(i, q) {
        int com, x, y;
        cin >> com >> x >> y;
        if (com == 0)
            st.apply(x, y);
        else
            co(st.prod(x, y + 1));
    }

    return 0;
}
