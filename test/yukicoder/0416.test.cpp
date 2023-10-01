#define PROBLEM "https://yukicoder.me/problems/no/416"
#include "template/atcoder.hpp"
#include "tree/partially_persistent_union_find.hpp"

int main(void) {
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<std::pair<int, int>> es(m);
    std::cin >> es;
    std::vector<std::pair<int, int>> queries(q);
    std::cin >> queries;
    std::reverse(all(queries));
    std::set<std::pair<int, int>> st(all(queries));

    partially_persistent_union_find uf(n);
    for (auto [a, b] : es) {
        if (!st.count({a, b})) uf.unite(a - 1, b - 1);
    }
    for (auto [a, b] : queries) uf.unite(a - 1, b - 1);

    rep (i, n) {
        if (!i) continue;
        if (!uf.same(0, i)) {
            co(0);
            continue;
        }
        if (uf.same(0, i, m - q)) {
            co(-1);
            continue;
        }
        auto check = [&](int mid) { return !uf.same(0, i, m - mid); };
        int l = q, r = -1;
        while (abs(l - r) > 1) {
            int mid = (l + r) / 2;
            (check(mid) ? l : r) = mid;
        }
        co(l);
    }

    return 0;
}
