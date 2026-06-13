// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2891
#include <iostream>
#include "graph/edge_input.hpp"
#include "graph/namori_graph.hpp"

int main(void) {
    int n;
    std::cin >> n;
    edge_input<void> ei(n);
    auto g = ei.to_undirected(n);
    auto parent = cycle_detection_on_namori_graph(g);
    int q;
    std::cin >> q;
    while (q--) {
        int a, b;
        std::cin >> a >> b;
        std::cout << (parent[a - 1] == -1 && parent[b - 1] == -1 ? 2 : 1) << '\n';
    }

    return 0;
}
