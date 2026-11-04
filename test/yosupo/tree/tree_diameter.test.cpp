// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/tree_diameter
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include "graph/edge_input.hpp"
#include "tree/tree_function.hpp"

int main(void) {
    int n;
    std::cin >> n;
    edge_input<int> ei(n - 1, 0);
    auto g = ei.to_undirected(n);
    auto d = tree_info<std::int64_t>(g, 0).dist;
    int st = std::max_element(d.begin(), d.end()) - d.begin();
    auto t = tree_info<std::int64_t>(g, st);
    d = t.dist;
    auto &p = t.parent;
    int gl = std::max_element(d.begin(), d.end()) - d.begin();
    std::vector<int> ans;
    while (gl != -1) {
        ans.emplace_back(gl);
        gl = p[gl];
    }
    std::cout << *std::max_element(d.begin(), d.end()) << ' ' << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');

    return 0;
}
