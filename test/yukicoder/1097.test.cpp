#define PROBLEM "https://yukicoder.me/problems/no/1097"
#include <cstdint>
#include <iostream>
#include <vector>
#include "algorithm/doubling.hpp"

struct Monoid {
    using value_type = std::int64_t;
    static constexpr std::int64_t id = 0;
    static constexpr std::int64_t op(const std::int64_t &lhs, const std::int64_t &rhs) {
        return lhs + rhs;
    }
};

int main(void) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    std::vector<int> to(n);
    for (int i = 0; i < n; ++i) to[i] = (i + a[i]) % n;
    Doubling<40, Monoid> db(to, a);
    int q;
    std::cin >> q;
    while (q--) {
        std::int64_t k;
        std::cin >> k;
        std::cout << db.solve(0, k).second << '\n';
    }

    return 0;
}
