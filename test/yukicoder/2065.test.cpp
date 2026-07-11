// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/2065
#include <cstdint>
#include <iostream>
#include <vector>
#include "wavelet/range_min_max_sum.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<std::int64_t> a(n);
    for (auto &x : a) std::cin >> x;

    RangeMinMaxSum<std::int64_t, std::int64_t> rms(a);
    while (q--) {
        int l, r;
        std::int64_t x;
        std::cin >> l >> r >> x;
        std::cout << rms.query_min(l - 1, r, x) << '\n';
    }

    return 0;
}
