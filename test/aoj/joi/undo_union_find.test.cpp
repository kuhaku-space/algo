// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/0723
#include "tree/undo_union_find.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

int main(void) {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::pair<int, int>> edges(m);
    for (auto &[x, y] : edges) std::cin >> x >> y, --x, --y;
    std::vector<int> s(n);
    for (int &e : s) std::cin >> e;
    int q;
    std::cin >> q;
    std::vector<std::pair<int, int>> queries(q);
    for (auto &[x, y] : queries) std::cin >> x >> y, --x, --y;

    undo_union_find uf(n);
    std::map<std::pair<int, int>, std::vector<int>> mp;
    for (int i = 0; i < m; ++i) {
        auto [x, y] = edges[i];
        if (s[x] == s[y]) {
            uf.unite(x, y);
        } else {
            if (s[x] > s[y]) std::swap(x, y);
            mp[{s[x], s[y]}].emplace_back(i);
        }
    }

    std::vector<int> ans(q, -1);
    std::map<std::pair<int, int>, std::vector<int>> pm;
    for (int i = 0; i < q; ++i) {
        auto [x, y] = queries[i];
        if (s[x] == s[y]) {
            ans[i] = uf.same(x, y);
        } else {
            if (s[x] > s[y]) std::swap(x, y);
            pm[{s[x], s[y]}].emplace_back(i);
        }
    }

    int snap = uf.snapshot();
    for (auto &[p, v] : pm) {
        for (auto e : mp[p]) uf.unite(edges[e].first, edges[e].second);
        for (auto e : v) ans[e] = uf.same(queries[e].first, queries[e].second);
        uf.rollback(snap);
    }

    for (int i = 0; i < q; ++i) std::cout << ans[i] << '\n';

    return 0;
}
