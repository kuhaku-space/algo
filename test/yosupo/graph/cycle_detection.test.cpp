// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/cycle_detection
#include <iostream>
#include <vector>
#include "graph/cycle.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;
    Graph<void> g(n);
    g.input_edge(m, 0);  // 有向辺。各辺 ID は入力順 0..m-1

    auto cycle = cycle_detection(g);
    if (cycle.empty()) {
        std::cout << -1 << '\n';
    } else {
        std::cout << cycle.size() << '\n';
        for (int e : cycle) std::cout << e << '\n';
    }

    return 0;
}
