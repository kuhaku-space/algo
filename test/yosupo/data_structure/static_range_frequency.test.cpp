// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/static_range_frequency
#include <iostream>
#include <vector>
#include "wavelet/compressed_wavelet_matrix.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    CompressedWaveletMatrix wm(a);
    while (q--) {
        int l, r, x;
        std::cin >> l >> r >> x;
        std::cout << wm.rank(l, r, x) << '\n';
    }

    return 0;
}
