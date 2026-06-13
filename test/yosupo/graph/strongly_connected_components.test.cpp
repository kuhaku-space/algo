// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/scc
#include <algorithm>
#include <iostream>
#include <vector>
#include "graph/edge_input.hpp"
#include "graph/scc.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    edge_input<void> ei(m, 0);
    auto g = ei.to_directed(n);
    auto v = scc(g);
    std::vector<std::vector<int>> ans(*std::max_element(v.begin(), v.end()) + 1);
    for (int i = 0; i < n; ++i) ans[v[i]].emplace_back(i);
    std::cout << ans.size() << '\n';
    for (auto &&u : ans) {
        std::cout << u.size();
        for (auto &e : u) std::cout << ' ' << e;
        std::cout << '\n';
    }

    return 0;
}
