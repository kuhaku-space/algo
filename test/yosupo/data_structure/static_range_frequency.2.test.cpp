// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/static_range_frequency
#include <iostream>
#include <vector>

#include "data_structure/merge_sort_tree.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int &e : a) std::cin >> e;
    merge_sort_tree<int> mst(a);
    while (q--) {
        int l, r, x;
        std::cin >> l >> r >> x;
        std::cout << mst.rank(l, r, x) << '\n';
    }

    return 0;
}
