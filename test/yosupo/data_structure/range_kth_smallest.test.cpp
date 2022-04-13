#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#include "matrix/compressed_wavelet_matrix.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;
    compressed_wavelet_matrix<int, 18> wm(a);

    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        co(wm.kth_smallest(l, r, k));
    }

    return 0;
}
