#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_C"
#include "graph/topological_sort.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;
    Graph<void> g(n);
    g.input_edge(m, true);

    co(has_cycle(g));

    return 0;
}
