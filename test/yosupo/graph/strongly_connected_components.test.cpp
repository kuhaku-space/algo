#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include "graph/scc.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    Graph<void> g(n);
    g.input_edge(m, 0);
    auto v = scc(g);
    std::vector<std::vector<int>> ans(*max_element(v.begin(), v.end()) + 1);
    rep (i, n) ans[v[i]].emplace_back(i);
    co(ans.size());
    for (auto &&u : ans) {
        co(u.size(), u);
    }

    return 0;
}
