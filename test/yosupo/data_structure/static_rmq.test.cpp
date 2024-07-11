// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/staticrmq
#include <iostream>
#include <vector>
#include "data_structure/sparse_table.hpp"
#include "segment_tree/monoid.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    sparse_table<Min<int>> st(a);
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << st.prod(l, r) << '\n';
    }

    return 0;
}
