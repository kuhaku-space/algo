// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_7_A
#include <iostream>
#include "flow/bipartite_matching.hpp"

int main(void) {
    int l, r, m;
    std::cin >> l >> r >> m;
    BipartiteMatching g(l, r);
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        g.add_edge(u, v);
    }
    std::cout << g.matching() << '\n';

    return 0;
}
