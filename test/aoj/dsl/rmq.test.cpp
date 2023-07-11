#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_A"
#include "segment_tree/segment_tree.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    segment_tree<Min<int>> st(n, (1LL << 31) - 1);
    while (q--) {
        int com, x, y;
        std::cin >> com >> x >> y;
        if (com == 0) st.set(x, y);
        else co(st.prod(x, y + 1));
    }

    return 0;
}
