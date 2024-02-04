#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"
#include <iostream>
#include <tuple>
#include <vector>

#include "algorithm/compress.hpp"
#include "data_structure/wavelet_matrix_monoid.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<std::tuple<int, int, int>> a(n);
    for (auto &[x, y, z] : a) std::cin >> x >> y >> z;
    std::sort(a.begin(), a.end());
    std::vector<std::int64_t> x(n), y(n), z(n);
    for (int i = 0; i < n; ++i) std::tie(x[i], y[i], z[i]) = a[i];

    wavelet_matrix_monoid<std::int64_t, Add<std::int64_t>, 30> wm(y, z);

    while (q--) {
        int l, d, r, u;
        std::cin >> l >> d >> r >> u;
        int lx = std::lower_bound(x.begin(), x.end(), l) - x.begin();
        int rx = std::lower_bound(x.begin(), x.end(), r) - x.begin();
        std::cout << wm.rect_sum(lx, rx, d, u) << '\n';
    }

    return 0;
}
