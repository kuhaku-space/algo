// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/tree_path_composite_sum
#include <iostream>
#include <utility>
#include <vector>
#include "math/modint.hpp"
#include "tree/rerooting.hpp"

using Mint = modint998;

template <class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) {
    return is >> p.first >> p.second;
}

struct Monoid {
    using T = std::pair<Mint, Mint>;
    using value_type = T;
    static constexpr T id() { return T(); }
    static constexpr T op(const T &lhs, const T &rhs) {
        return {lhs.first + rhs.first, lhs.second + rhs.second};
    }

    template <class U>
    static constexpr T f(const T &v, U u) {
        return {u.first * v.first + u.second * v.second, v.second};
    }

    template <class U>
    static constexpr T g(const T &v, U u) {
        return {v.first + u, v.second + 1};
    }
};

int main(void) {
    int n;
    std::cin >> n;
    std::vector<Mint> a(n);
    for (auto &e : a) std::cin >> e;
    Graph<std::pair<Mint, Mint>> g(n);
    g.input_edges(n - 1, 0);
    ReRooting<Monoid, std::pair<Mint, Mint>, Mint> rr(g, a);
    std::vector<Mint> ans;
    for (int i = 0; i < n; ++i) ans.emplace_back(rr[i].first);
    for (int i = 0; i < (int)ans.size(); ++i)
        std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');

    return 0;
}
