// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2880
#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
#include "binary_tree/range_set.hpp"

int main(void) {
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<std::tuple<int, int, int, int, int>> queries;
    for (int i = 0; i < m; ++i) {
        int d, a, b;
        std::cin >> d >> a >> b;
        queries.emplace_back(d, 1, i, a, b);
    }
    for (int i = 0; i < q; ++i) {
        int e, s, t;
        std::cin >> e >> s >> t;
        queries.emplace_back(e, 0, i, s, t - 1);
    }

    std::sort(queries.begin(), queries.end());
    std::vector<bool> ans(q);
    range_set<int> rs;
    for (auto [a, b, c, d, e] : queries) {
        if (b == 0) ans[c] = d > e || rs.same(d, e);
        else rs.insert(d, e);
    }
    for (auto f : ans) std::cout << (f ? "Yes\n" : "No\n");

    return 0;
}
