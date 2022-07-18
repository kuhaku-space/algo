#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
#include "math/modint.hpp"
#include "segment_tree/lazy_segment_tree.hpp"
#include "template/atcoder.hpp"

using Mint = ModInt<>;

struct M1 {
    using T = pair<Mint, Mint>;
    using value_type = T;
    static constexpr T id = T(0, 0);
    static constexpr T op(T lhs, T rhs) { return {lhs.first + rhs.first, rhs.second + lhs.second}; }
};

struct M2 {
    using T = pair<Mint, Mint>;
    using value_type = T;
    static constexpr T id = T(1, 0);
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
    cin >> n >> q;
    vector<Mint> a(n);
    cin >> a;
    vector<pair<Mint, Mint>> p(n);
    rep (i, n) p[i] = {a[i], 1};
    lazy_segment_tree<M1, M2> st(p);

    while (q--) {
        int c;
        cin >> c;
        if (c == 0) {
            int l, r, b, c;
            cin >> l >> r >> b >> c;
            st.apply(l, r, {b, c});
        } else {
            int l, r;
            cin >> l >> r;
            co(st.prod(l, r).first);
        }
    }

    return 0;
}
