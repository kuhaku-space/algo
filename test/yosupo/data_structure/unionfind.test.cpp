#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include <iostream>
#include "tree/union_find.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    union_find uf(n);
    while (q--) {
        int t, u, v;
        std::cin >> t >> u >> v;
        if (t == 0) uf.unite(u, v);
        else std::cout << uf.same(u, v) << '\n';
    }

    return 0;
}
