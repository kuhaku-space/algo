// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/3163
#include <cstdint>
#include <iostream>
#include <utility>
#include "graph/edge_input.hpp"
#include "tree/rerooting.hpp"

struct Monoid {
    using T = std::pair<std::int64_t, std::int64_t>;
    using value_type = T;
    static constexpr T id() { return {0, 0}; };
    static constexpr T op(const T &lhs, const T &rhs) { return {lhs.first + rhs.first, lhs.second + rhs.second}; }

    template <class U>
    static constexpr T f(const T &v, U u) {
        return {v.first + v.second, v.second};
    }

    template <class U>
    static constexpr T g(const T &v, U u) {
        return {v.first, v.second + u};
    }
};

int main(void) {
    int n;
    std::cin >> n;
    std::vector<std::int64_t> a(n);
    for (auto &e : a) std::cin >> e;
    edge_input<void> ei(n - 1);
    auto g = ei.to_undirected(n);

    ReRooting<Monoid, csr_graph<void>, std::int64_t> rr(g, a);
    for (int i = 0; i < n; ++i) std::cout << rr[i].first << '\n';

    return 0;
}
