// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_A
#include <algorithm>
#include <iostream>
#include <vector>
#include "graph/edge_input.hpp"
#include "graph/lowlink.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    edge_input<void> ei(m, 0);
    auto g = ei.to_undirected(n);

    low_link llink(g);
    auto ans = llink.get_articulation_points();
    std::sort(ans.begin(), ans.end());
    for (auto e : ans) std::cout << e << '\n';

    return 0;
}
