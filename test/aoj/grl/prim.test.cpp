// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_2_A
#include "graph/prim.hpp"
#include <iostream>

int main(void) {
    int n, m;
    std::cin >> n >> m;
    Graph<int> g(n);
    g.input_edges(m, 0);
    auto v = prim(g);
    int ans = 0;
    for (auto &e : v) ans += e.weight();
    std::cout << ans << '\n';

    return 0;
}
