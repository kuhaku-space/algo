#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_A"
#include "graph/lowlink.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;
    Graph<void> g(n);
    g.input_edges(m, 0);

    LowLink llink(g);

    auto ans = llink.get_articulation_points();
    std::sort(all(ans));
    for (auto i : ans) co(i);

    return 0;
}
