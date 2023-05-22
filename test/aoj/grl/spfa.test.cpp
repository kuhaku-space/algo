#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B"
#include "graph/spfa.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, m, r;
    cin >> n >> m >> r;
    Graph<int> g(n);
    g.input_edge(m, 0);

    auto dist = shortest_path_faster_algorithm(g, r, Inf);
    if (dist.empty()) {
        co("NEGATIVE CYCLE");
        return 0;
    }
    rep (i, n) {
        if (dist[i] != Inf) co(dist[i]);
        else co("INF");
    }

    return 0;
}
