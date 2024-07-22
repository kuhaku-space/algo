// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1977
#include <cstdint>
#include <iostream>
#include <vector>
#include "algorithm/doubling.hpp"
#include "template/template.hpp"

struct Monoid {
    using T = std::int64_t;
    using value_type = T;
    static constexpr T id() { return 0; }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs + rhs; }
};

int main(void) {
    std::int64_t n, m, l;
    std::cin >> n >> m >> l;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    std::vector<int> to(n);
    for (int i = 0; i < n; ++i) to[i] = (i + l) % n;
    Doubling<40, Monoid> db(to, a);
    std::int64_t r = (n * m) % l;
    std::int64_t k = (n * m) / l;
    std::int64_t ans = -INF;
    for (int i = 0; i < std::min(r, n); ++i) chmax(ans, db.solve(i, k + 1).second);
    for (int i = 0; i < std::min(l - r, n); ++i) chmax(ans, db.solve((r + i) % n, k).second);
    std::cout << ans << '\n';

    return 0;
}
