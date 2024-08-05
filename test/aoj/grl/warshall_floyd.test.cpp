// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_C
#include "graph/warshall_floyd.hpp"
#include <cstdint>
#include <iostream>
#include <string>
#include "graph/matrix_graph.hpp"

int main(void) {
    int v, e;
    std::cin >> v >> e;
    matrix_graph<std::int64_t> g(v, INF);
    while (e--) {
        int s, t, d;
        std::cin >> s >> t >> d;
        g.add_edge(s, t, d);
    }
    floyd_warshall(g);
    for (int i = 0; i < v; ++i) {
        if (g[i][i] < 0) {
            std::cout << "NEGATIVE CYCLE\n";
            return 0;
        }
    }

    for (int i = 0; i < v; ++i) {
        for (int j = 0; j < v; ++j) {
            if (g[i][j] >= INF / 2) std::cout << "INF";
            else std::cout << g[i][j];
            if (j == v - 1) std::cout << '\n';
            else std::cout << ' ';
        }
    }

    return 0;
}
