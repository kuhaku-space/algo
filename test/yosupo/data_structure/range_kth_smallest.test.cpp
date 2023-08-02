#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#include "data_structure/compressed_wavelet_matrix.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    std::cin >> a;
    compressed_wavelet_matrix<int, 18> wm(a);

    while (q--) {
        int l, r, k;
        std::cin >> l >> r >> k;
        co(wm.kth_smallest(l, r, k));
    }

    return 0;
}
