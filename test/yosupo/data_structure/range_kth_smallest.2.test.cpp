#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#include "data_structure/wavelet_matrix.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    std::cin >> a;
    wavelet_matrix<int, 30> wm(a);

    while (q--) {
        int l, r, k;
        std::cin >> l >> r >> k;
        co(wm.kth_smallest(l, r, k));
    }

    return 0;
}
