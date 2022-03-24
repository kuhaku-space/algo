#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/4/GRL_4_B"
#include "graph/topological_sort.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;
    Graph<void> g(n);
    g.input_edge(m, true);

    auto v = topological_sort(g);
    for (auto e : v) co(e);

    return 0;
}