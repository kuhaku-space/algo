// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/0516
#include "data_structure/priority_k_sum.hpp"
#include <algorithm>
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
        maximum_sum<int> ms(k);
        int ans = std::numeric_limits<int>::lowest();
        for (int i = 0; i < n; ++i) {
            ms.insert(a[i]);
            if (i >= k) ms.erase(a[i - k]);
            if (ms.size() == k) ans = std::max(ans, ms.query());
        }
        std::cout << ans << '\n';
    }
    return 0;
}
