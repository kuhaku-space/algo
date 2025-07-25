// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_A
#include <algorithm>
#include <iostream>
#include <vector>
#include "graph/lowlink.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    Graph<void> g(n);
    g.input_edges(m, 0);

    low_link llink(g);
    auto ans = llink.get_articulation_points();
    std::sort(ans.begin(), ans.end());
    for (auto e : ans) std::cout << e << '\n';

    return 0;
}
