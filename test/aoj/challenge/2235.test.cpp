// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2235
#include <iostream>
#include <utility>
#include <vector>
#include "data_structure/offline_dynamic_connectivity.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    offline_dynamic_connectivity dc(n, q);
    std::vector<std::tuple<int, int, int>> v(q);
    for (int i = 0; i < q; ++i) {
        auto &[a, b, c] = v[i];
        std::cin >> a >> b >> c;
        if (a == 1) dc.add(i, b, c);
        else if (a == 2) dc.erase(i, b, c);
    }
    dc.build();
    std::vector<int> ans(q);
    auto f = [&](int x) {
        auto [a, b, c] = v[x];
        if (a == 3) ans[x] = dc.same(b, c);
    };
    dc.solve(f);
    for (int i = 0; i < q; ++i) {
        auto [a, b, c] = v[i];
        if (a == 3) std::cout << (ans[i] ? "YES\n" : "NO\n");
    }

    return 0;
}
