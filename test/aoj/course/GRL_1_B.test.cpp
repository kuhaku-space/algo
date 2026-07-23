// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>
#include "graph/edge_input.hpp"
#include "graph/shortest_path.hpp"

int main(void) {
    int n, m, r;
    std::cin >> n >> m >> r;
    edge_input<int> ei(m, 0);
    auto g = ei.to_directed(n);

    auto dist_spfa = shortest_path_spfa(g, r);
    auto dist_negative = shortest_path_negative(g, r);

    bool has_negative_cycle = dist_spfa.empty();
    bool has_negative_cycle_from_sentinel = false;
    for (int i = 0; i < n; ++i) {
        if (dist_negative[i] == std::numeric_limits<int>::lowest()) has_negative_cycle_from_sentinel = true;
    }
    assert(has_negative_cycle == has_negative_cycle_from_sentinel);

    if (has_negative_cycle) {
        std::cout << "NEGATIVE CYCLE\n";
        return 0;
    }

    assert(dist_spfa == dist_negative);
    for (int i = 0; i < n; ++i) {
        if (dist_spfa[i] != std::numeric_limits<int>::max()) std::cout << dist_spfa[i] << '\n';
        else std::cout << "INF\n";
    }

    return 0;
}
