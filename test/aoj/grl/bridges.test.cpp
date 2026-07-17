// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_B
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include "graph/lowlink.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    Graph<void> g(n);
    g.input_edges(m, 0);

    low_link llink(g);
    std::vector<std::pair<int, int>> ans;
    for (int id : llink.get_bridges()) {
        auto &e = g.get_edge(id);
        if (e.from() < e.to()) ans.emplace_back(e.from(), e.to());
        else ans.emplace_back(e.to(), e.from());
    }

    std::sort(ans.begin(), ans.end());
    for (auto e : ans) std::cout << e.first << ' ' << e.second << '\n';

    return 0;
}
