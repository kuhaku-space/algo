#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"
#include "data_structure/compressed_wavelet_matrix.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    std::cin >> a;
    compressed_wavelet_matrix wm(a);

    while (q--) {
        int l, r, x;
        std::cin >> l >> r >> x;
        co(wm.rank(l, r, x));
    }

    return 0;
}
