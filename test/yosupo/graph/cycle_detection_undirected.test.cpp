// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/cycle_detection_undirected
#include <iostream>
#include <vector>
#include "graph/cycle.hpp"
#include "graph/edge_input.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;
    edge_input<void> ei(m, 0);
    auto g = ei.to_undirected(n);  // 往復 2 本に同じ ID（= 入力辺番号）が振られる

    auto [vs, es] = cycle_detection_undirected(g);
    if (vs.empty()) {
        std::cout << -1 << '\n';
    } else {
        int L = vs.size();
        std::cout << L << '\n';
        for (int i = 0; i < L; ++i) std::cout << vs[i] << " \n"[i + 1 == L];
        for (int i = 0; i < L; ++i) std::cout << es[i] << " \n"[i + 1 == L];
    }

    return 0;
}
