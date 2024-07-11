// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_I
#include <iostream>
#include <limits>
#include <utility>
#include "segment_tree/lazy_segment_tree.hpp"

struct M1 {
    using T = std::pair<int, int>;
    using value_type = T;
    static constexpr T id = T(0, 0);
    static constexpr T op(T lhs, T rhs) { return {lhs.first + rhs.first, lhs.second + rhs.second}; }
};

struct M2 {
    using T = int;
    using value_type = T;
    static constexpr T id = std::numeric_limits<int>::max();
    static constexpr T op(T lhs, T rhs) { return lhs == id ? rhs : lhs; }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs == id ? rhs : U{lhs * rhs.second, rhs.second};
    }
};

int main(void) {
    int n, q;
    std::cin >> n >> q;
    lazy_segment_tree<M1, M2> st(n, {0, 1});
    while (q--) {
        int com;
        std::cin >> com;
        if (com == 0) {
            int s, t, x;
            std::cin >> s >> t >> x;
            st.apply(s, t + 1, x);
        } else {
            int s, t;
            std::cin >> s >> t;
            std::cout << st.prod(s, t + 1).first << std::endl;
        }
    }

    return 0;
}
