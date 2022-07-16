#define PROBLEM "https://judge.yosupo.jp/problem/chromatic_number"
#include "graph/chromatic_number.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, m;
    cin >> n >> m;
    matrix_graph<void> g(n);
    g.input_edges(m, 0);
    co(chromatic_number(g));

    return 0;
}
