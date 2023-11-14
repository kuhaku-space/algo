#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_A"
#include <iostream>
#include "segment_tree/dynamic_segment_tree.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    dynamic_segment_tree<Min<int>> st(n);
    while (q--) {
        int com, x, y;
        std::cin >> com >> x >> y;
        if (com == 0) st.set(x, y);
        else std::cout << st.prod(x, y + 1) << std::endl;
    }

    return 0;
}
