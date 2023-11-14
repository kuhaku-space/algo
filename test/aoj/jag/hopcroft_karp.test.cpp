#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2251"
#include "flow/hopcroft_karp.hpp"
#include <algorithm>
#include <iostream>
#include "graph/matrix_graph.hpp"
#include "graph/warshall_floyd.hpp"

int main(void) {
    while (true) {
        int n, m, l;
        std::cin >> n >> m >> l;
        if (!n) break;
        matrix_graph<int> g(n, Inf);
        while (m--) {
            int u, v, w;
            std::cin >> u >> v >> w;
            g.add_edges(u, v, w);
        }
        warshall_floyd(g);
        std::vector<std::pair<int, int>> q(l);
        for (auto &[a, b] : q) std::cin >> a >> b;
        std::sort(q.begin(), q.end(), [](auto l, auto r) { return l.second < r.second; });
        hopcroft_karp hk(l, l);
        for (int i = 0; i < l; ++i) {
            auto [a, b] = q[i];
            for (int j = i + 1; j < l; ++j) {
                auto [c, d] = q[j];
                if (b + g[a][c] <= d) hk.add_edge(i, j);
            }
        }
        std::cout << l - hk.matching() << std::endl;
    }

    return 0;
}
