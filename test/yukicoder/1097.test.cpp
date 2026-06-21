// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1097
#include <cstdint>
#include <iostream>
#include <vector>
#include "algorithm/doubling.hpp"
#include "segtree/monoid.hpp"

int main(void) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    std::vector<int> to(n);
    for (int i = 0; i < n; ++i) to[i] = (i + a[i]) % n;
    doubling<40, Add<std::int64_t>> db(to, a);
    int q;
    std::cin >> q;
    while (q--) {
        std::int64_t k;
        std::cin >> k;
        std::cout << db.solve(0, k).second << '\n';
    }

    return 0;
}
