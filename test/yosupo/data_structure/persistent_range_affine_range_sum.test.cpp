// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/persistent_range_affine_range_sum
#include <iostream>
#include <utility>
#include <vector>
#include "math/modint.hpp"
#include "persistent_ds/persistent_lazy_segment_tree.hpp"

using Mint = modint998;

struct S {
    using T = std::pair<Mint, Mint>;
    using value_type = T;
    static constexpr T id() { return T(); }
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
    std::vector<Mint> a(n);
    for (auto &e : a) std::cin >> e;
    std::vector<std::pair<Mint, Mint>> p(n);
    for (int i = 0; i < n; ++i) p[i] = {a[i], 1};
    std::vector<persistent_lazy_segment_tree<S, F>> st(q + 1);
    st[0] = persistent_lazy_segment_tree<S, F>(p);
    for (int i = 1; i <= q; ++i) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int k, l, r, b, c;
            std::cin >> k >> l >> r >> b >> c;
            st[i] = st[k + 1].apply(l, r, {b, c});
        } else if (t == 1) {
            int k, s, l, r;
            std::cin >> k >> s >> l >> r;
            st[i] = st[k + 1].copy(l, r, st[s + 1]);
        } else {
            int k, l, r;
            std::cin >> k >> l >> r;
            std::cout << st[k + 1].prod(l, r).first << '\n';
        }
    }

    return 0;
}
