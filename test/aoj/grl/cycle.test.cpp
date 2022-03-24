#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/4/GRL_4_A"
#include "graph/cycle.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;
    Graph<void> g(n);
    g.input_edge(m, 0);

    co(has_cycle(g));

    return 0;
}
