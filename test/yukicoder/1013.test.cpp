// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1013
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
    int n, k;
    std::cin >> n >> k;
    std::vector<int> p(n);
    for (auto &e : p) std::cin >> e;
    std::vector<int> to(n);
    for (int i = 0; i < n; ++i) to[i] = (i + p[i]) % n;
    Doubling<30, Monoid> db(to, p);
    for (int i = 0; i < n; ++i) std::cout << i + 1 + db.solve(i, k).second << '\n';

    return 0;
}
