#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_G"
#include "binary_tree/BIT_RAQ.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();

    int n, q;
    cin >> n >> q;

    BIT_RAQ<ll> bit(n);
    while (q--) {
        int com;
        cin >> com;
        if (com == 0) {
            int s, t, x;
            cin >> s >> t >> x;
            bit.add(s - 1, t, x);
        } else {
            int s, t;
            cin >> s >> t;
            co(bit.sum(s - 1, t));
        }
    }

    return 0;
}
