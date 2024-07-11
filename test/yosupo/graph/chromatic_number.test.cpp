// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/chromatic_number
#include "graph/chromatic_number.hpp"
#include <iostream>

int main(void) {
    int n, m;
    std::cin >> n >> m;
    matrix_graph<void> g(n);
    g.input_edges(m, 0);
    std::cout << chromatic_number(g) << '\n';

    return 0;
}
