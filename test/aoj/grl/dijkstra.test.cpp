// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_A
#include "graph/dijkstra.hpp"
#include <iostream>
#include <vector>
#include "graph/graph.hpp"

int main(void) {
    int n, m, r;
    std::cin >> n >> m >> r;
    Graph<int> g(n);
    g.input_edge(m, 0);

    int inf = std::numeric_limits<int>::max();
    auto dist = dijkstra(g, r, inf);
    for (int i = 0; i < n; ++i) {
        if (dist[i] != inf) std::cout << dist[i] << '\n';
        else std::cout << "INF\n";
    }

    return 0;
}
