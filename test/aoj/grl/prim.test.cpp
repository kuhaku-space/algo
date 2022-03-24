#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/2/GRL_2_A"
#include "graph/prim.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;
    Graph<int> g(n);
    g.input_edges(m, 0);
    auto v = prim(g);

    int ans = 0;
    for (auto &e : v) {
        ans += e.weight();
    }
    co(ans);

    return 0;
}
