// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_B
#include <iostream>
#include <vector>
#include "graph/edge_input.hpp"
#include "graph/topological_sort.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    edge_input<void> ei(m, 0);
    auto g = ei.to_directed(n);

    auto v = topological_sort(g);
    for (auto &e : v) std::cout << e << '\n';

    return 0;
}
