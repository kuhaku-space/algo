#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_B"
#include "graph/lowlink.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;
    Graph<void> g(n);
    g.input_edges(m, true);

    LowLink lowlink(g);

    auto ans = lowlink.get_bridges();
    for (auto &e : ans) {
        if (e.first > e.second)
            swap(e.first, e.second);
    }

    std::sort(all(ans));
    for (auto e : ans) {
        co(e.first, e.second);
    }

    return 0;
}
