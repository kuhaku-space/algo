// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/unionfind_with_potential_non_commutative_group
#include <array>
#include <iostream>
#include "math/modint.hpp"
#include "union_find/potentialized_union_find.hpp"

using Mint = modint998;

/// SL(2, MOD)：det = 1 の 2x2 行列がなす非可換群
struct sl2 {
    std::array<std::array<Mint, 2>, 2> a;

    /// デフォルト構築で単位行列
    sl2() : a{{{Mint(1), Mint(0)}, {Mint(0), Mint(1)}}} {}

    sl2 operator*(const sl2 &rhs) const {
        sl2 res;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) res.a[i][j] = a[i][0] * rhs.a[0][j] + a[i][1] * rhs.a[1][j];
        }
        return res;
    }

    /// det = 1 を仮定した逆行列
    sl2 inv() const {
        sl2 res;
        res.a[0][0] = a[1][1];
        res.a[0][1] = -a[0][1];
        res.a[1][0] = -a[1][0];
        res.a[1][1] = a[0][0];
        return res;
    }

    bool operator==(const sl2 &rhs) const { return a == rhs.a; }
};

int main(void) {
    int n, q;
    std::cin >> n >> q;
    potentialized_union_find<sl2> uf(n);
    while (q--) {
        int t, u, v;
        std::cin >> t >> u >> v;
        if (t == 0) {
            sl2 x;
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) std::cin >> x.a[i][j];
            }
            // a[u] = a[v] * x  =>  a[v]^{-1} * a[u] = x
            std::cout << uf.valid(v, u, x) << '\n';
        } else {
            if (uf.same(u, v)) {
                sl2 d = uf.diff(v, u);  // a[v]^{-1} * a[u]
                std::cout << d.a[0][0] << ' ' << d.a[0][1] << ' ' << d.a[1][0] << ' ' << d.a[1][1] << '\n';
            } else {
                std::cout << -1 << '\n';
            }
        }
    }

    return 0;
}
