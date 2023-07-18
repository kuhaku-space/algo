#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_A"
#include "segment_tree/segment_tree_raq.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, q;
    cin >> n >> q;
    segment_tree_range_add_range_min<int> st(n, std::numeric_limits<int>::max());
    while (q--) {
        int com, x, y;
        cin >> com >> x >> y;
        if (com == 0) st.set(x, y);
        else co(st.prod(x, y + 1));
    }

    return 0;
}
