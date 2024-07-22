// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_affine_range_sum
#include <iostream>
#include <utility>
#include <vector>
#include "math/modint.hpp"
#include "segment_tree/lazy_segment_tree.hpp"

using Mint = modint998;

struct M1 {
    using T = std::pair<Mint, Mint>;
    using value_type = T;
    static constexpr T id() { return T(); }
    static constexpr T op(T lhs, T rhs) { return {lhs.first + rhs.first, rhs.second + lhs.second}; }
};

struct M2 {
    using T = std::pair<Mint, Mint>;
    using value_type = T;
    static constexpr T id() { return T(1, 0); }
    static constexpr T op(T lhs, T rhs) {
        return {lhs.first * rhs.first, lhs.first * rhs.second + lhs.second};
    }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return {lhs.first * rhs.first + lhs.second * rhs.second, rhs.second};
    }
};

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<Mint> a(n);
    for (auto &e : a) std::cin >> e;
    std::vector<std::pair<Mint, Mint>> p(n);
    for (int i = 0; i < n; ++i) p[i] = {a[i], 1};
    lazy_segment_tree<M1, M2> st(p);

    while (q--) {
        int c;
        std::cin >> c;
        if (c == 0) {
            int l, r, b, c;
            std::cin >> l >> r >> b >> c;
            st.apply(l, r, {b, c});
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << st.prod(l, r).first << '\n';
        }
    }

    return 0;
}
