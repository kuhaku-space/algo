// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/dominatortree
#include <iostream>
#include "graph/dominator_tree.hpp"

int main() {
    int n, m, s;
    std::cin >> n >> m >> s;
    Graph<void> g(n);
    g.input_edge(m, 0);

    dominator_tree dt(g, s);
    for (int i = 0; i < n; ++i) {
        std::cout << (dt.idom(i) == -1 ? i : dt.idom(i)) << " \n"[i + 1 == n];
    }

    return 0;
}
