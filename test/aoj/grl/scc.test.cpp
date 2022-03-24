#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_C"
#include "graph/scc.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;
    Graph<void> g(n);
    g.input_edge(m, 0);

    auto v = scc(g);
    int q;
    cin >> q;
    while (q--) {
        int s, t;
        cin >> s >> t;
        co(v[s] == v[t]);
    }

    return 0;
}
