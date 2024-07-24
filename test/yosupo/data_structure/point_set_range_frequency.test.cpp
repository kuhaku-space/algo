// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_set_range_frequency
#include <iostream>
#include <vector>

#include "data_structure/dynamic_wavelet_matrix.hpp"
#include "segment_tree/monoid.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int &e : a) std::cin >> e;
    dynamic_wavelet_matrix<int, 30> wm(a);
    while (q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int k, v;
            std::cin >> k >> v;
            wm.erase(k);
            wm.insert(k, v);
        } else {
            int l, r, x;
            std::cin >> l >> r >> x;
            std::cout << wm.rank(l, r, x) << '\n';
        }
    }

    return 0;
}
