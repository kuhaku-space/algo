#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_7_A"
#include "flow/hopcroft_karp.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int l, r, m;
    std::cin >> l >> r >> m;
    hopcroft_karp g(l, r);
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        g.add_edge(u, v);
    }
    co(g.matching());

    return 0;
}
