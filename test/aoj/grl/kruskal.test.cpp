// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_2_A
#include "graph/edge_input.hpp"
#include "graph/kruskal.hpp"
#include <iostream>
#include <vector>

int main(void) {
    int n, m;
    std::cin >> n >> m;
    edge_input<int> ei(m, 0);
    Graph<int> g(n);
    ei.build_undirected(g);
    auto v = kruskal(g);

    int ans = 0;
    for (auto &e : v) ans += e.weight();
    std::cout << ans << '\n';

    return 0;
}
