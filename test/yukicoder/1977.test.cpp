// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1977
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>
#include "algorithm/doubling.hpp"
#include "segtree/monoid.hpp"

int main(void) {
    std::int64_t n, m, l;
    std::cin >> n >> m >> l;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    std::vector<int> to(n);
    for (int i = 0; i < n; ++i) to[i] = (i + l) % n;
    doubling<40, Add<std::int64_t>> db(to, a);
    std::int64_t r = (n * m) % l;
    std::int64_t k = (n * m) / l;
    std::int64_t ans = std::numeric_limits<std::int64_t>::min();
    for (int i = 0; i < std::min(r, n); ++i) ans = std::max(ans, db.solve(i, k + 1).second);
    for (int i = 0; i < std::min(l - r, n); ++i) ans = std::max(ans, db.solve((r + i) % n, k).second);
    std::cout << ans << '\n';

    return 0;
}
