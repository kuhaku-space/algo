// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/674
#include <algorithm>
#include <cstdint>
#include <iostream>
#include "binary_tree/range_set.hpp"

int main(void) {
    std::int64_t d;
    int q;
    std::cin >> d >> q;
    range_set<std::int64_t> rst;
    std::int64_t ans = 0;
    while (q--) {
        std::int64_t l, r;
        std::cin >> l >> r;
        auto [x, y] = rst.insert(l, r + 1);
        ans = std::max(ans, y - x);
        std::cout << ans << '\n';
    }

    return 0;
}
