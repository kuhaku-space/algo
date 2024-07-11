// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_7_A
#include <iostream>
#include "flow/max_flow.hpp"

int main(void) {
    int x, y, e;
    std::cin >> x >> y >> e;
    mf_graph<int> mf(x + y + 2);
    while (e--) {
        int s, t;
        std::cin >> s >> t;
        mf.add_edge(s, x + t, 1);
    }

    int s = x + y, t = s + 1;
    for (int i = 0; i < x; ++i) mf.add_edge(s, i, 1);
    for (int i = 0; i < y; ++i) mf.add_edge(x + i, t, 1);
    std::cout << mf.flow(s, t) << std::endl;

    return 0;
}
