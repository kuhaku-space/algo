#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/7/ITP2_7_B"
#include "binary_tree/scapegoat_tree.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int q;
    cin >> q;
    int size = 0;
    scapegoat_tree<int> st;
    rep(i, q) {
        int x, y;
        cin >> x >> y;
        if (x == 0) {
            if (!st.contains(y)) {
                st.insert(y);
                ++size;
            }
            co(size);
        } else if (x == 1) {
            co(st.contains(y));
        } else if (x == 2) {
            if (st.contains(y)) {
                st.erase(y);
                --size;
            }
        }
    }

    return 0;
}
