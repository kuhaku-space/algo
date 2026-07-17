// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2871
#include <iostream>
#include <vector>
#include "segtree/lazy_segment_tree.hpp"
#include "tree/euler_tour.hpp"

struct S {
    int g, w;
};

struct M {
    using value_type = S;
    static constexpr S id() { return S{0, 0}; }
    static constexpr S op(const S &lhs, const S &rhs) { return S{lhs.g + rhs.g, lhs.w + rhs.w}; }
};

struct F {
    using T = int;
    using value_type = int;
    static constexpr T id() { return 0; }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs ^ rhs; }

    static S f(const T &lhs, S rhs) {
        if (lhs == 0) return rhs;
        std::swap(rhs.g, rhs.w);
        return rhs;
    }
};

int main(void) {
    int n, q;
    std::cin >> n >> q;
    Graph<void> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int p;
        std::cin >> p;
        g.add_edges(p - 1, i + 1);
    }
    euler_tour et(g);
    std::vector<S> v(n);
    for (int i = 0; i < n; ++i) {
        char c;
        std::cin >> c;
        if (c == 'G') v[et.left(i)] = S{1, 0};
        else v[et.left(i)] = S{0, 1};
    }
    lazy_segment_tree<M, F> lst(v);
    while (q--) {
        int x;
        std::cin >> x;
        --x;
        auto [l, r] = et[x];
        lst.apply(l, r, 1);
        auto [g, w] = lst.all_prod();
        if (g >= w) std::cout << "broccoli\n";
        else std::cout << "cauliflower\n";
    }

    return 0;
}
