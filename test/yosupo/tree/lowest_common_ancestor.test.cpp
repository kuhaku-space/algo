#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "template/atcoder.hpp"
#include "tree/hld.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> p(n - 1);
    std::cin >> p;
    HLD hld(n);
    rep (i, n - 1) hld.add_edges(p[i], i + 1);
    hld.build();
    while (q--) {
        int u, v;
        std::cin >> u >> v;
        co(hld.lca(u, v));
    }

    return 0;
}
