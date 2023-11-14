#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_C"
#include "graph/scc.hpp"
#include <iostream>
#include <vector>

int main(void) {
    int n, m;
    std::cin >> n >> m;
    Graph<void> g(n);
    g.input_edge(m, 0);

    auto v = scc(g);
    int q;
    std::cin >> q;
    while (q--) {
        int s, t;
        std::cin >> s >> t;
        std::cout << (v[s] == v[t]) << std::endl;
    }

    return 0;
}
