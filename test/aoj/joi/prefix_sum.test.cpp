// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/0516
#include "algorithm/prefix_sum.hpp"
#include <iostream>
#include <limits>
#include <vector>

int main(void) {
    while (true) {
        int n, k;
        std::cin >> n >> k;
        if (!n) break;
        std::vector<int> a(n);
        for (auto &e : a) std::cin >> e;
        prefix_sum<int> ps(a);
        int ans = std::numeric_limits<int>::lowest();
        for (int i = 0; i < n - k + 1; ++i) ans = std::max(ans, ps.sum(i, i + k));
        std::cout << ans << '\n';
    }

    return 0;
}
