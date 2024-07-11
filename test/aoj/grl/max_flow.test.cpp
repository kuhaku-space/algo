// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A
#include "flow/max_flow.hpp"
#include <iostream>

int main(void) {
    int n, m;
    std::cin >> n >> m;

    mf_graph<int> mf(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        mf.add_edge(a, b, c);
    }
    std::cout << mf.flow(0, n - 1) << std::endl;

    return 0;
}
