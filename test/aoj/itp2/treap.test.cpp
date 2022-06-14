#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/7/ITP2_7_B"
#include "binary_tree/treap.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int q;
    cin >> q;
    int size = 0;
    Treap<int> treap;
    rep(i, q) {
        int x, y;
        cin >> x >> y;
        if (x == 0) {
            if (!treap.contains(y)) {
                treap.insert(y);
                ++size;
            }
            co(size);
        } else if (x == 1) {
            co(treap.contains(y));
        } else if (x == 2) {
            if (treap.contains(y)) {
                treap.erase(y);
                --size;
            }
        }
    }

    return 0;
}
