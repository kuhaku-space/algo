// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_B
#include "graph/topological_sort.hpp"
#include <iostream>
#include <vector>

int main(void) {
    int n, m;
    std::cin >> n >> m;
    Graph<void> g(n);
    g.input_edge(m, 0);

    auto v = topological_sort(g);
    for (auto &e : v) std::cout << e << '\n';

    return 0;
}
