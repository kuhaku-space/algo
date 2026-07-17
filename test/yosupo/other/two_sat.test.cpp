// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/two_sat
#include "graph/two_sat.hpp"
#include <iostream>
#include <string>

int main(void) {
    std::string tmp;
    int n, m;
    std::cin >> tmp >> tmp >> n >> m;
    two_sat ts(n);
    while (m--) {
        int a, b, c;
        std::cin >> a >> b >> c;
        bool f = true, g = true;
        if (a < 0) a = -a, f = false;
        if (b < 0) b = -b, g = false;
        ts.add(a - 1, f, b - 1, g);
    }
    auto v = ts.solve();
    if (!ts.is_satisfy(v)) {
        std::cout << "s UNSATISFIABLE\n";
        return 0;
    }
    std::cout << "s SATISFIABLE\n";
    auto u = ts.build(v);
    std::vector<int> ans(n);
    for (int i = 0; i < n; ++i) ans[i] = (u[i] ? i + 1 : -i - 1);
    std::cout << "v ";
    for (auto &&e : ans) std::cout << e << ' ';
    std::cout << 0 << '\n';

    return 0;
}
