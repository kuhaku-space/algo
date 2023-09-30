#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2871"
#include "segment_tree/lazy_segment_tree.hpp"
#include "template/atcoder.hpp"
#include "tree/eular_tour.hpp"

struct S {
    int g, w;
};

struct M {
    using value_type = S;
    static constexpr value_type id = S{0, 0};
    static constexpr value_type op(const value_type &lhs, const value_type &rhs) {
        return S{lhs.g + rhs.g, lhs.w + rhs.w};
    }
};

struct F {
    using value_type = int;
    static constexpr value_type id = 0;
    static constexpr value_type op(const value_type &lhs, const value_type &rhs) {
        return lhs ^ rhs;
    }

    static S f(const value_type &lhs, S rhs) {
        if (lhs == 0) return rhs;
        std::swap(rhs.g, rhs.w);
        return rhs;
    }
};

int main(void) {
    int n, q;
    std::cin >> n >> q;
    Graph<void> g(n);
    rep (i, n - 1) {
        int p;
        std::cin >> p;
        g.add_edges(p - 1, i + 1);
    }
    eular_tour et(g);
    std::vector<S> v(n);
    rep (i, n) {
        char c;
        std::cin >> c;
        if (c == 'G') v[et.get_l(i)] = S{1, 0};
        else v[et.get_l(i)] = S{0, 1};
    }
    lazy_segment_tree<M, F> lst(v);
    while (q--) {
        int x;
        std::cin >> x;
        --x;
        lst.apply(et.get_l(x), et.get_r(x), 1);
        auto [g, w] = lst.all_prod();
        if (g >= w) co("broccoli");
        else co("cauliflower");
    }

    return 0;
}
