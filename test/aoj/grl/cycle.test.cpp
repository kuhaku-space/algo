// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_A
#include "graph/cycle.hpp"
#include <iostream>
#include "graph/edge_input.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    edge_input<void> ei(m, 0);
    auto g = ei.to_directed(n);
    std::cout << has_cycle(g) << '\n';

    return 0;
}
