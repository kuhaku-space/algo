// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/maximum_independent_set
#include "graph/maximum_independent_set.hpp"
#include <iostream>
#include <vector>
#include "graph/edge_input.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    edge_input<void> ei(m, 0);
    auto g = ei.to_undirected(n);
    auto ans = maximum_independent_set(g);
    std::cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');

    return 0;
}
