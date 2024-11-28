// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/unionfind_with_potential
#include <iostream>
#include <vector>
#include "math/modint.hpp"
#include "tree/weighted_union_find.hpp"

using Mint = modint998;

int main(void) {
    int n, q;
    std::cin >> n >> q;
    weighted_union_find<Mint> uf(n);
    while (q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int u, v;
            Mint x;
            std::cin >> u >> v >> x;
            if (uf.same(u, v)) std::cout << (uf.diff(v, u) == x) << '\n';
            else std::cout << uf.unite(v, u, x) << '\n';
        } else {
            int u, v;
            std::cin >> u >> v;
            if (uf.same(u, v)) std::cout << uf.diff(v, u) << '\n';
            else std::cout << -1 << '\n';
        }
    }

    return 0;
}
