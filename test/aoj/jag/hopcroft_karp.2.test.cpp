// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2976
#include "flow/hopcroft_karp.hpp"
#include <iostream>
#include <set>
#include <utility>
#include <vector>
#include "tree/union_find.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> a(m);
    for (auto &[x, y] : a) std::cin >> x >> y, --x, --y;

    hopcroft_karp mf(n, n);
    for (int i = 0; i < m; ++i) {
        auto [x, y] = a[i];
        mf.add_edge(x, y);
    }
    int ansX = m - mf.matching();

    union_find uf(n * 2 + m);
    for (int i = 0; i < m; ++i) {
        auto [x, y] = a[i];
        uf.unite(i, m + x);
        uf.unite(i, m + n + y);
    }
    std::set<int> st;
    for (int i = 0; i < m; ++i) st.emplace(uf.root(i));
    int ansY = m - st.size();

    std::cout << ansX << ' ' << ansY << '\n';

    return 0;
}
