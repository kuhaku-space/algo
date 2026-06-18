// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_A
#include "graph/shortest_path.hpp"
#include <iostream>
#include <vector>
#include "graph/edge_input.hpp"
#include "heap/dary_heap.hpp"

int main(void) {
    int n, m, r;
    std::cin >> n >> m >> r;
    edge_input<int> ei(m, 0);
    auto g = ei.to_directed(n);

    int inf = std::numeric_limits<int>::max();
    // ヒープを 4 分ヒープに差し替える（lazy-deletion 経路）。
    auto dist = shortest_path<quaternary_heap>(g, r, inf);
    for (int i = 0; i < n; ++i) {
        if (dist[i] != inf) std::cout << dist[i] << '\n';
        else std::cout << "INF\n";
    }

    return 0;
}
