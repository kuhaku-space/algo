// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/0516
#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>
#include "algorithm/prefix_sum.hpp"
#include "heap/priority_k_sum.hpp"

int main(void) {
    while (true) {
        int n, k;
        std::cin >> n >> k;
        if (!n) break;
        std::vector<int> a(n);
        for (auto &e : a) std::cin >> e;

        // 累積和で長さ k の区間和の最大値を求める版。
        PrefixSum<int> ps(a);
        int ans_prefix = std::numeric_limits<int>::lowest();
        for (int i = 0; i < n - k + 1; ++i) ans_prefix = std::max(ans_prefix, ps.sum(i, i + k));

        // スライディングウィンドウを維持しながら上位 k 件の和を求める版。
        maximum_sum<int> ms(k);
        int ans_heap = std::numeric_limits<int>::lowest();
        for (int i = 0; i < n; ++i) {
            ms.insert(a[i]);
            if (i >= k) ms.erase(a[i - k]);
            if (ms.size() == k) ans_heap = std::max(ans_heap, ms.query());
        }

        assert(ans_prefix == ans_heap);
        std::cout << ans_prefix << '\n';
    }

    return 0;
}
