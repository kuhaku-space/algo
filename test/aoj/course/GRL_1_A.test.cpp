// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_A
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>
#include "graph/edge_input.hpp"
#include "graph/shortest_path.hpp"
#include "heap/dary_heap.hpp"
#include "heap/fibonacci_heap.hpp"

int main(void) {
    int n, m, r;
    std::cin >> n >> m >> r;
    edge_input<int> ei(m, 0);
    auto g = ei.to_directed(n);

    int inf = std::numeric_limits<int>::max();
    auto dist = shortest_path(g, r, inf);
    auto dist_fib = shortest_path<fibonacci_heap>(g, r, inf);
    auto dist_dary = shortest_path<quaternary_heap>(g, r, inf);
    assert(dist == dist_fib);
    assert(dist == dist_dary);

    for (int i = 0; i < n; ++i) {
        if (dist[i] != inf) std::cout << dist[i] << '\n';
        else std::cout << "INF\n";
    }

    return 0;
}
