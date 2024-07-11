// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2891

#include "graph/namori_graph.hpp"
#include <iostream>
#include "graph/graph.hpp"

int main(void) {
    int n;
    std::cin >> n;
    Graph<void> g(n);
    g.input_edges(n);
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
