// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/1595
#include <iostream>
#include "graph/edge_input.hpp"
#include "graph/subdivide_edges.hpp"
#include "tree/tree_function.hpp"

int main(void) {
    int n;
    std::cin >> n;
    edge_input<void> ei(n - 1);
    auto g = ei.to_undirected(n);
    // 中点を足した木では中心が 1 頂点になり、離心数は (中心までの距離) + (直径 / 2) の半分
    auto tc = tree_center(subdivide_edges(g));
    for (int v = 0; v < n; ++v) std::cout << 2 * (n - 1) - (tc.dist[v] + tc.diameter / 2) / 2 << '\n';

    return 0;
}
