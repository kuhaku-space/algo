#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include "tree/tree_function.hpp"

int main(void) {
    int n;
    std::cin >> n;
    Graph<int> g(n);
    g.input_edges(n - 1, 0);
    auto d = tree_dist<int, std::int64_t>(g, 0);
    int st = std::max_element(d.begin(), d.end()) - d.begin();
    d = tree_dist<int, std::int64_t>(g, st);
    auto p = tree_parent(g, st);
    int gl = std::max_element(d.begin(), d.end()) - d.begin();
    std::vector<int> ans;
    while (gl != -1) {
        ans.emplace_back(gl);
        gl = p[gl];
    }
    std::cout << *std::max_element(d.begin(), d.end()) << ' ' << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i)
        std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');

    return 0;
}
