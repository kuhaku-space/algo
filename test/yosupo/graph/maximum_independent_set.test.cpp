#define PROBLEM "https://judge.yosupo.jp/problem/maximum_independent_set"
#include "graph/maximum_independent_set.hpp"
#include <iostream>
#include <vector>

int main(void) {
    int n, m;
    std::cin >> n >> m;
    Graph<void> g(n);
    g.input_edges(m, 0);
    auto ans = maximum_independent_set(g);
    std::cout << ans.size() << '\n';
    for (auto &&e : ans) std::cout << e << '\n';

    return 0;
}
