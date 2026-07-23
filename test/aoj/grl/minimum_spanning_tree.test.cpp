// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_2_A
#include <cassert>
#include <iostream>
#include <vector>
#include "graph/edge_input.hpp"
#include "graph/kruskal.hpp"
#include "graph/prim.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    edge_input<int> ei(m, 0);
    auto g = ei.to_undirected(n);

    auto edges_kruskal = kruskal(g);
    auto edges_prim = prim(g);

    int ans_kruskal = 0;
    for (auto &e : edges_kruskal) ans_kruskal += e.weight();
    int ans_prim = 0;
    for (auto &e : edges_prim) ans_prim += e.weight();
    assert(ans_kruskal == ans_prim);

    std::cout << ans_kruskal << '\n';

    return 0;
}
