// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_2_A
#include <iostream>
#include <vector>
#include "graph/edge_input.hpp"
#include "graph/kruskal.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    edge_input<int> ei(m, 0);
    auto g = ei.to_undirected(n);
    auto v = kruskal(g);

    int ans = 0;
    for (auto &e : v) ans += e.weight();
    std::cout << ans << '\n';

    return 0;
}
