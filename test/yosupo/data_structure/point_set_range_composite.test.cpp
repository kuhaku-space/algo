#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"
#include "math/modint.hpp"
#include "segment_tree/segment_tree.hpp"
#include "template/atcoder.hpp"

using Mint = ModInt<>;

struct M {
    using T = pair<Mint, Mint>;
    using value_type = T;
    static constexpr T id = T(1, 0);
    static constexpr T op(T lhs, T rhs) {
        return {rhs.first * lhs.first, rhs.first * lhs.second + rhs.second};
    }
};

int main(void) {
    int n, q;
    cin >> n >> q;
    vector<pair<Mint, Mint>> p(n);
    cin >> p;
    segment_tree<M> st(p);

    while (q--) {
        int c;
        cin >> c;
        if (c == 0) {
            int k, a, b;
            cin >> k >> a >> b;
            st.set(k, {a, b});
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            auto p = st.prod(l, r);
            co(p.first * x + p.second);
        }
    }

    return 0;
}
