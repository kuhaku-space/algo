// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/1595
#include <iostream>
#include "graph/edge_input.hpp"
#include "tree/tree_function.hpp"

int main(void) {
    int n;
    std::cin >> n;
    edge_input<void> ei(n - 1);
    auto g = ei.to_undirected(n);
    auto tc = tree_center(g);
    // 頂点 v の離心数は dist[v] + ceil(diameter / 2)。最も遠い頂点への道だけ戻らずに済む
    for (int v = 0; v < n; ++v) std::cout << 2 * (n - 1) - (tc.dist[v] + (tc.diameter + 1) / 2) << '\n';

    return 0;
}
