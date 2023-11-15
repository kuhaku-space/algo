#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
#include <iostream>
#include "flow/hopcroft_karp.hpp"

int main(void) {
    int l, r, m;
    std::cin >> l >> r >> m;
    hopcroft_karp g(l, r);
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        g.add_edge(u, v);
    }
    std::cout << g.matching() << '\n';
    for (auto p : g.get_pairs()) std::cout << p.first << ' ' << p.second << '\n';

    return 0;
}
