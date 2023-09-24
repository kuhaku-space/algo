#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2251"
#include "flow/hopcroft_karp.hpp"
#include "graph/matrix_graph.hpp"
#include "graph/warshall_floyd.hpp"
#include "template/atcoder.hpp"

int main(void) {
    while (true) {
        int n, m, l;
        std::cin >> n >> m >> l;
        if (!n) break;
        matrix_graph<int> g(n, Inf);
        while (m--) {
            int u, v, w;
            cin >> u >> v >> w;
            g.add_edges(u, v, w);
        }
        warshall_floyd(g);
        std::vector<std::pair<int, int>> q(l);
        std::cin >> q;
        sort(all(q), [](auto l, auto r) {
            return l.second < r.second;
        });
        hopcroft_karp hk(l, l);
        rep (i, l) {
            auto [a, b] = q[i];
            FOR (j, i + 1, l) {
                auto [c, d] = q[j];
                if (b + g[a][c] <= d) hk.add_edge(i, j);
            }
        }
        co(l - hk.matching());
    }

    return 0;
}
