#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<std::int64_t> a(n);
    for (auto &e : a) std::cin >> e;
    a.emplace_back(0);
    std::inclusive_scan(a.rbegin(), a.rend(), a.rbegin());
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << a[l] - a[r] << '\n';
    }

    return 0;
}
