// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B
#include <iostream>
#include <limits>
#include <vector>
#include "graph/edge_input.hpp"
#include "graph/shortest_path.hpp"

int main(void) {
    int n, m, r;
    std::cin >> n >> m >> r;
    edge_input<int> ei(m, 0);
    auto g = ei.to_directed(n);

    auto dist = shortest_path_spfa(g, r);
    if (dist.empty()) {
        std::cout << "NEGATIVE CYCLE\n";
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        if (dist[i] != std::numeric_limits<int>::max()) std::cout << dist[i] << '\n';
        else std::cout << "INF\n";
    }

    return 0;
}
