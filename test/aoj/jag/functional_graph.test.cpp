// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2970
#include "graph/functional_graph.hpp"
#include <iostream>
#include <vector>
#include "math/chinese_rem.hpp"

int main(void) {
    int n;
    std::cin >> n;
    std::vector<int> p(n), q(n);
    for (int &e : p) std::cin >> e, --e;
    for (int &e : q) std::cin >> e, --e;

    functional_graph fg(q);
    std::vector<int> b(n), m(n);
    for (int i = 0; i < n; ++i) {
        b[i] = fg.dist(p[i], i);
        if (b[i] == -1) {
            std::cout << -1 << '\n';
            return 0;
        }
        m[i] = fg.cycle(i);
    }
    auto [x, y] = chinese_rem(b, m);
    std::cout << (y == -1 ? -1 : x) << '\n';

    return 0;
}
