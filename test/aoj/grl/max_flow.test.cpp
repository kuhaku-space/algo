#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_A"
#include "flow/max_flow.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;

    mf_graph<int> mf(n);
    rep(i, m) {
        int a, b, c;
        cin >> a >> b >> c;
        mf.add_edge(a, b, c);
    }

    co(mf.flow(0, n - 1));

    return 0;
}
