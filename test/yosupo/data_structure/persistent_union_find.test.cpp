// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/persistent_unionfind
#include "tree/persistent_union_find.hpp"
#include <iostream>
#include <vector>

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<persistent_union_find> ufs;
    ufs.emplace_back(n);
    while (q--) {
        int t, k, u, v;
        std::cin >> t >> k >> u >> v;
        if (t == 0) {
            ufs.emplace_back(ufs[k + 1].unite(u, v));
        } else {
            std::cout << ufs[k + 1].same(u, v) << '\n';
            ufs.emplace_back();
        }
    }

    return 0;
}
