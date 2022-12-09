#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/7/GRL_7_A"
#include "flow/max_flow.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int x, y, e;
    cin >> x >> y >> e;
    mf_graph<int> mf(x + y + 2);
    while (e--) {
        int s, t;
        cin >> s >> t;
        mf.add_edge(s, x + t, 1);
    }

    int s = x + y, t = s + 1;
    for (int i = 0; i < x; ++i) mf.add_edge(s, i, 1);
    for (int i = 0; i < y; ++i) mf.add_edge(x + i, t, 1);
    co(mf.flow(s, t));

    return 0;
}
