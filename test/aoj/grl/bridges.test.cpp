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

    auto bridges = lowlink.get_bridges();
    vector<pair<int, int>> ans;
    for (auto &e : bridges) {
        if (e.from() < e.to())
            ans.emplace_back(e.from(), e.to());
        else
            ans.emplace_back(e.to(), e.from());
    }

    std::sort(all(ans));
    for (auto e : ans) { co(e.first, e.second); }

    return 0;
}
