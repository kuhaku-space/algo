// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B
#include "graph/edge_input.hpp"
#include "graph/shortest_path.hpp"
#include <iostream>

int main(void) {
    int n, m, r;
    std::cin >> n >> m >> r;
    edge_input<int> ei(m, 0);
    auto g = ei.to_directed(n);

    auto dist = shortest_path_negative(g, r);
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
