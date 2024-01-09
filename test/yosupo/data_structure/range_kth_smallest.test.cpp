#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#include <iostream>
#include <vector>
#include "data_structure/compressed_wavelet_matrix.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    compressed_wavelet_matrix<int, 18> wm(a);
    while (q--) {
        int l, r, k;
        std::cin >> l >> r >> k;
        std::cout << wm.kth_smallest(l, r, k) << '\n';
    }

    return 0;
}
