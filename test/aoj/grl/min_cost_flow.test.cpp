#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_B"
#include "flow/min_cost_flow.hpp"
#include <iostream>

int main(void) {
    int n, m, f;
    std::cin >> n >> m >> f;

    mcf_graph<int, int> mf(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        mf.add_edge(a, b, c, d);
    }
    auto ans = mf.flow(0, n - 1, f);
    std::cout << (ans.first == f ? ans.second : -1) << std::endl;

    return 0;
}
