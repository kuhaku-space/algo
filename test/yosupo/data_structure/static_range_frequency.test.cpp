// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/static_range_frequency
#include <cassert>
#include <iostream>
#include <vector>
#include "data_structure/merge_sort_tree.hpp"
#include "wavelet/compressed_wavelet_matrix.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    CompressedWaveletMatrix wm(a);
    merge_sort_tree<int> mst(a);
    while (q--) {
        int l, r, x;
        std::cin >> l >> r >> x;
        int ans_wm = wm.rank(l, r, x);
        int ans_mst = mst.rank(l, r, x);
        assert(ans_wm == ans_mst);
        std::cout << ans_wm << '\n';
    }

    return 0;
}
