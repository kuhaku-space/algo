// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/staticrmq
#include <cassert>
#include <iostream>
#include <vector>
#include "data_structure/disjoint_sparse_table.hpp"
#include "data_structure/linear_sparse_table.hpp"
#include "data_structure/sparse_table.hpp"
#include "segtree/monoid.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    sparse_table<Min<int>> st(a);
    disjoint_sparse_table<Min<int>> st_disjoint(a);
    linear_sparse_table<Min<int>> st_linear(a);
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        int ans = st.prod(l, r);
        assert(ans == st_disjoint.prod(l, r));
        assert(ans == st_linear.prod(l, r));
        std::cout << ans << '\n';
    }

    return 0;
}
