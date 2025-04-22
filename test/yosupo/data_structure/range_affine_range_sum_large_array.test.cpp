// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_affine_range_sum
#include <iostream>
#include <utility>
#include <vector>
#include "math/modint.hpp"
#include "segtree/dynamic_lazy_segment_tree.hpp"

using Mint = modint998;

struct S {
    using T = std::pair<Mint, Mint>;
    using value_type = T;
    static constexpr T id() { return T(); }
    static constexpr T id(std::int64_t x) { return T(0, x); }
    static constexpr T op(T lhs, T rhs) { return {lhs.first + rhs.first, rhs.second + lhs.second}; }
};

struct F {
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
    dynamic_lazy_segment_tree<S, F> st(n);
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
