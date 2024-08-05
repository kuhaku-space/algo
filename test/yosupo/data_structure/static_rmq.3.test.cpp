// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/staticrmq
#include <iostream>
#include <vector>
#include "data_structure/linear_sparse_table.hpp"
#include "segment_tree/monoid.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    linear_sparse_table<Min<int>> lst(a);
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << lst.prod(l, r) << '\n';
    }

    return 0;
}
