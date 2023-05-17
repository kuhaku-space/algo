#define PROBLEM "https://judge.yosupo.jp/problem/tree_path_composite_sum"
#include "math/modint.hpp"
#include "template/atcoder.hpp"
#include "tree/rerooting.hpp"

using Mint = modint998;

struct Monoid {
    using value_type = pair<Mint, Mint>;
    static constexpr value_type id = {0, 0};
    static inline vector<Mint> a = vector<Mint>();
    static constexpr value_type op(const value_type &lhs, const value_type &rhs) {
        return {lhs.first + rhs.first, lhs.second + rhs.second};
    }

    template <class T>
    static constexpr value_type f(const value_type &v, T u) {
        return {u.first * v.first + u.second * v.second, v.second};
    }

    static value_type g(const value_type &v, int u) { return {v.first + a[u], v.second + 1}; }
};

int main(void) {
    int n;
    cin >> n;
    Monoid::a = vector<Mint>(n);
    cin >> Monoid::a;
    Graph<pair<Mint, Mint>> g(n);
    g.input_edges(n - 1, 0);
    ReRooting<Monoid, pair<Mint, Mint>> rr(g);
    vector<Mint> ans;
    rep (i, n) ans.emplace_back(rr[i].first);
    co(ans);

    return 0;
}
