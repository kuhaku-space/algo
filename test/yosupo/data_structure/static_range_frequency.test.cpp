#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"
#include "matrix/compressed_wavelet_matrix.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;
    compressed_wavelet_matrix wm(a);

    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        co(wm.rank(l, r, x));
    }

    return 0;
}
