// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_set_range_composite_large_array
#include <iostream>
#include "math/modint.hpp"
#include "segtree/dynamic_segment_tree.hpp"

using Mint = modint998;

int main(void) {
    int n, q;
    std::cin >> n >> q;
    dynamic_segment_tree<Rev<Affine<Mint>>> dst(n);
    while (q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int p, c, d;
            std::cin >> p >> c >> d;
            dst.set(p, {c, d});
        } else {
            int l, r, x;
            std::cin >> l >> r >> x;
            auto [c, d] = dst.prod(l, r);
            std::cout << c * x + d << '\n';
        }
    }

    return 0;
}
