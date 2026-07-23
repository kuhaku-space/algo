// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_kth_smallest
#include <cassert>
#include <iostream>
#include <vector>
#include "wavelet/compressed_wavelet_matrix.hpp"
#include "wavelet/wavelet_matrix.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    CompressedWaveletMatrix<int, 18> cwm(a);
    WaveletMatrix<int, 30> wm(a);
    while (q--) {
        int l, r, k;
        std::cin >> l >> r >> k;
        int ans_cwm = cwm.kth_smallest(l, r, k);
        int ans_wm = wm.kth_smallest(l, r, k);
        assert(ans_cwm == ans_wm);
        std::cout << ans_cwm << '\n';
    }

    return 0;
}
