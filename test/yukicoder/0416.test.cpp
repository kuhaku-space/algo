#define PROBLEM "https://yukicoder.me/problems/no/416"
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include "tree/partially_persistent_union_find.hpp"

int main(void) {
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<std::pair<int, int>> es(m);
    for (auto &[a, b] : es) std::cin >> a >> b;
    std::vector<std::pair<int, int>> queries(q);
    for (auto &[a, b] : queries) std::cin >> a >> b;
    std::reverse(queries.begin(), queries.end());
    std::set<std::pair<int, int>> st(queries.begin(), queries.end());

    partially_persistent_union_find uf(n);
    for (auto [a, b] : es) {
        if (!st.count({a, b})) uf.unite(a - 1, b - 1);
    }
    for (auto [a, b] : queries) uf.unite(a - 1, b - 1);

    for (int i = 1; i < n; ++i) {
        if (!uf.same(0, i)) {
            std::cout << 0 << '\n';
            continue;
        }
        if (uf.same(0, i, m - q)) {
            std::cout << -1 << '\n';
            continue;
        }
        auto check = [&](int mid) { return !uf.same(0, i, m - mid); };
        int l = q, r = -1;
        while (abs(l - r) > 1) {
            int mid = (l + r) / 2;
            (check(mid) ? l : r) = mid;
        }
        std::cout << l << '\n';
    }

    return 0;
}
