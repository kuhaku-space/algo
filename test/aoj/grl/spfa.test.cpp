// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B
#include "graph/spfa.hpp"
#include <iostream>
#include <vector>

int main(void) {
    int n, m, r;
    std::cin >> n >> m >> r;
    Graph<int> g(n);
    g.input_edge(m, 0);

    auto dist = shortest_path_faster_algorithm(g, r, Inf);
    if (dist.empty()) {
        std::cout << "NEGATIVE CYCLE" << std::endl;
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        if (dist[i] != Inf) std::cout << dist[i] << std::endl;
        else std::cout << "INF" << std::endl;
    }

    return 0;
}
