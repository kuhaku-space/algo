// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_set_range_composite
#include <iostream>
#include <utility>
#include <vector>
#include "math/modint.hpp"
#include "segment_tree/segment_tree.hpp"

using Mint = modint998;

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<std::pair<Mint, Mint>> p(n);
    for (auto &[a, b] : p) std::cin >> a >> b;
    segment_tree<Rev<Affine<Mint>>> st(p);

    while (q--) {
        int c;
        std::cin >> c;
        if (c == 0) {
            int k, a, b;
            std::cin >> k >> a >> b;
            st.set(k, {a, b});
        } else {
            int l, r, x;
            std::cin >> l >> r >> x;
            auto p = st.prod(l, r);
            std::cout << (p.first * x + p.second) << '\n';
        }
    }

    return 0;
}
