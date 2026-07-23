// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_A
#include <cassert>
#include <iostream>
#include <limits>
#include "segtree/dynamic_segment_tree.hpp"
#include "segtree/lazy_segment_tree.hpp"
#include "segtree/monoid.hpp"
#include "segtree/segment_tree.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    segment_tree<Min<int>> st(n, std::numeric_limits<int>::max());
    lazy_segment_tree<Min<int>, Add<int>> st_lazy(n, std::numeric_limits<int>::max());
    dynamic_segment_tree<Min<int>> st_dynamic(n);
    while (q--) {
        int com, x, y;
        std::cin >> com >> x >> y;
        if (com == 0) {
            st[x] = y;
            st_lazy.set(x, y);
            st_dynamic.set(x, y);
        } else {
            int ans = st.prod(x, y + 1);
            assert(ans == st_lazy.prod(x, y + 1));
            assert(ans == st_dynamic.prod(x, y + 1));
            std::cout << ans << '\n';
        }
    }

    return 0;
}
