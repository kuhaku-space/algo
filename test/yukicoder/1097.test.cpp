// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1097
#include <cstdint>
#include <iostream>
#include <vector>
#include "algorithm/doubling.hpp"

struct Monoid {
    using T = std::int64_t;
    using value_type = T;
    static constexpr T id() { return 0; }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs + rhs; }
};

int main(void) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    std::vector<int> to(n);
    for (int i = 0; i < n; ++i) to[i] = (i + a[i]) % n;
    doubling<40, Monoid> db(to, a);
    int q;
    std::cin >> q;
    while (q--) {
        std::int64_t k;
        std::cin >> k;
        std::cout << db.solve(0, k).second << '\n';
    }

    return 0;
}
