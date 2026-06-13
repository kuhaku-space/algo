// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_C
#include "graph/edge_input.hpp"
#include "graph/scc.hpp"
#include <iostream>
#include <vector>

int main(void) {
    int n, m;
    std::cin >> n >> m;
    edge_input<void> ei(m, 0);
    auto g = ei.to_directed(n);

    auto v = scc(g);
    int q;
    std::cin >> q;
    while (q--) {
        int s, t;
        std::cin >> s >> t;
        std::cout << (v[s] == v[t]) << '\n';
    }

    return 0;
}
