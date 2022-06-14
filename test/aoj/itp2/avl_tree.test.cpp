#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/7/ITP2_7_B"
#include "binary_tree/avl_tree.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int q;
    cin >> q;
    int size = 0;
    avl_tree<int> at;
    rep(i, q) {
        int x, y;
        cin >> x >> y;
        if (x == 0) {
            if (!at.contains(y)) {
                at.insert(y);
                ++size;
            }
            co(size);
        } else if (x == 1) {
            co(at.contains(y));
        } else if (x == 2) {
            if (at.contains(y)) {
                at.erase(y);
                --size;
            }
        }
    }

    return 0;
}
