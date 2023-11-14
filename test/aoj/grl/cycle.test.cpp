#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_A"
#include "graph/cycle.hpp"
#include <iostream>

int main(void) {
    int n, m;
    std::cin >> n >> m;
    Graph<void> g(n);
    g.input_edge(m, 0);
    std::cout << has_cycle(g) << std::endl;

    return 0;
}
