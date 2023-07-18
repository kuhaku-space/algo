#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
#include "flow/max_flow.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int l, r, m;
    std::cin >> l >> r >> m;
    std::vector<std::pair<int, int>> p(m);
    std::cin >> p;
    mf_graph<int> mf(l + r + 2);
    int s = l + r, g = s + 1;
    for (auto &&x : p) mf.add_edge(x.first, l + x.second, 1);
    rep (i, l) mf.add_edge(s, i, 1);
    rep (i, r) mf.add_edge(l + i, g, 1);
    mf.flow(s, g);
    std::vector<int> ans;
    rep (i, m) {
        if (mf.get_edge(i).flow == 1) ans.emplace_back(i);
    }
    co(ans.size());
    for (auto &&x : ans) co(p[x].first, p[x].second);

    return 0;
}
