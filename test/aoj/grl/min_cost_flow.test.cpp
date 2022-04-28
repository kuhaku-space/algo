#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_B"
#include "flow/min_cost_flow.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, m, f;
    cin >> n >> m >> f;

    mcf_graph<int, int> mf(n);
    rep(i, m) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        mf.add_edge(a, b, c, d);
    }

    auto ans = mf.flow(0, n - 1, f);
    if (ans.first == f)
        co(ans.second);
    else
        co(-1);

    return 0;
}
