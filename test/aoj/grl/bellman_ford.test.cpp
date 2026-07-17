// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B
#include "graph/bellman_ford.hpp"
#include <iostream>

int main(void) {
    int n, m, r;
    std::cin >> n >> m >> r;
    Graph<int> g(n);
    g.input_edge(m, 0);

    auto dist = bellman_ford(g, r);
    for (int i = 0; i < n; ++i) {
        if (dist[i] == std::numeric_limits<int>::lowest()) {
            std::cout << "NEGATIVE CYCLE\n";
            return 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (dist[i] != std::numeric_limits<int>::max()) std::cout << dist[i] << '\n';
        else std::cout << "INF\n";
    }

    return 0;
}
