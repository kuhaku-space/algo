#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_A"
#include "graph/dijkstra.hpp"
#include <iostream>
#include <vector>
#include "graph/graph.hpp"

int main(void) {
    int n, m, r;
    std::cin >> n >> m >> r;
    Graph<int> g(n);
    g.input_edge(m, 0);

    auto dist = dijkstra(g, r, Inf);
    for (int i = 0; i < n; ++i) {
        if (dist[i] != Inf) std::cout << dist[i] << std::endl;
        else std::cout << "INF" << std::endl;
    }

    return 0;
}
