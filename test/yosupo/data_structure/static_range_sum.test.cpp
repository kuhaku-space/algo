// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/static_range_sum
#include <cstdint>
#include <iostream>
#include <vector>
#include "algorithm/prefix_sum.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<std::int64_t> a(n);
    for (auto &e : a) std::cin >> e;
    prefix_sum<std::int64_t> ps(a);
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << ps.sum(l, r) << '\n';
    }
    return 0;
}
