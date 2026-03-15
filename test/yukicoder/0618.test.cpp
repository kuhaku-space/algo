// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/618
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>
#include "algorithm/compress.hpp"
#include "segtree/segment_tree.hpp"

struct S {
    std::int64_t x, s;
};

struct M {
    using T = S;
    using value_type = T;
    static constexpr T id() {
        return T(std::numeric_limits<std::int64_t>::max() / 2, 0);
    }
    static constexpr T op(const T& lhs, const T& rhs) {
        return S{std::min(lhs.x, rhs.x), lhs.s + rhs.s};
    }
};

int main(void) {
    int q;
    std::cin >> q;
    std::vector<int> t(q), x(q);
    for (int i = 0; i < q; ++i) std::cin >> t[i] >> x[i];

    std::int64_t s = 0;
    std::vector<std::int64_t> a;
    for (int i = 0; i < q; ++i) {
        if (t[i] == 1)
            a.emplace_back(x[i] - s);
        else if (t[i] == 3)
            s += x[i];
    }

    s = 0;
    coordinate_compression cps(a);
    segment_tree<M> st(cps.size());
    std::vector<std::int64_t> c;
    for (int i = 0; i < q; ++i) {
        if (t[i] == 1) {
            int k = cps.get(x[i] - s);
            c.emplace_back(x[i] - s);
            st.set(k, S{x[i] - s, st.get(k).s + 1});
        } else if (t[i] == 2) {
            int k = cps.get(c[x[i] - 1]);
            st.set(k, S{c[x[i] - 1], st.get(k).s - 1});
        } else {
            s += x[i];
        }
        auto f = [&](S y) {
            return y.x + s >= y.s;
        };
        int k = st.min_left(f);
        auto t = st.prod(k, cps.size());
        std::int64_t ans = std::min(t.x + s, t.s);
        if (k > 0) {
            t = st.prod(k - 1, cps.size());
            ans = std::max(ans, std::min(t.x + s, t.s));
        }
        std::cout << ans << '\n';
    }

    return 0;
}
