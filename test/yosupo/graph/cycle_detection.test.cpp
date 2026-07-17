// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/cycle_detection
#include <iostream>
#include <vector>
#include "graph/cycle.hpp"
#include "graph/edge_input.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;
    edge_input<void> ei(m, 0);
    auto g = ei.to_directed_graph(n);  // 各辺 ID は入力順 0..m-1

    auto cycle = cycle_detection_directed(g);
    if (cycle.empty()) {
        std::cout << -1 << '\n';
    } else {
        std::cout << cycle.size() << '\n';
        for (int e : cycle) std::cout << e << '\n';
    }

    return 0;
}
