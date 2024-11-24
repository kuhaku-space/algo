// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2834
#include "graph/dijkstra.hpp"
#include <cstdint>
#include <iostream>
#include <vector>
#include "graph/graph.hpp"

int main(void) {
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    --s, --t;
    std::vector<int> d(n);
    for (auto &e : d) std::cin >> e;
    Graph<std::int64_t> g(n * 2);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        --a, --b;
        g.add_edge(a * 2 + 1, b * 2, 0);
    }
    for (int i = 0; i < n; ++i) g.add_edge(i * 2, i * 2 + 1, d[i]);
    for (int i = 0; i < n - 1; ++i) g.add_edge(i * 2 + 3, i * 2 + 1, 0);
    auto dist = dijkstra(g, s * 2 + 1);
    std::cout << dist[t * 2 + 1] << '\n';

    return 0;
}
