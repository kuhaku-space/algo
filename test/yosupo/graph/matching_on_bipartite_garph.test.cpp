#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
#include <iostream>
#include <utility>
#include <vector>
#include "flow/max_flow.hpp"

int main(void) {
    int l, r, m;
    std::cin >> l >> r >> m;
    std::vector<std::pair<int, int>> p(m);
    for (auto &[a, b] : p) std::cin >> a >> b;
    mf_graph<int> mf(l + r + 2);
    int s = l + r, g = s + 1;
    for (auto &&x : p) mf.add_edge(x.first, l + x.second, 1);
    for (int i = 0; i < l; ++i) mf.add_edge(s, i, 1);
    for (int i = 0; i < r; ++i) mf.add_edge(l + i, g, 1);
    mf.flow(s, g);
    std::vector<int> ans;
    for (int i = 0; i < m; ++i) {
        if (mf.get_edge(i).flow == 1) ans.emplace_back(i);
    }
    std::cout << ans.size() << '\n';
    for (auto &&x : ans) std::cout << p[x].first << ' ' << p[x].second << '\n';

    return 0;
}
