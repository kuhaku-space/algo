// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/dominatortree
#include "graph/dominator_tree.hpp"
#include <iostream>
#include "graph/edge_input.hpp"

int main() {
    int n, m, s;
    std::cin >> n >> m >> s;
    edge_input<void> ei(m, 0);
    auto g = ei.to_directed_graph(n);

    dominator_tree dt(g, s);
    for (int i = 0; i < n; ++i) std::cout << dt.idom(i) << " \n"[i + 1 == n];

    return 0;
}
