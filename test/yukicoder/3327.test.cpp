// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/3327
#include <iostream>
#include <vector>
#include "segtree/segment_tree.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    std::vector<std::pair<int, int>> b(n);
    for (int i = 0; i < n; ++i) b[i] = {a[i], i};
    segment_tree<Max<std::pair<int, int>>> seg(b);
    while (q--) {
        int c, x;
        std::cin >> c >> x;
        if (c == 1) {
            auto f = [&](auto p) { return p.first <= x; };
            int k = seg.max_right(f);
            if (k == n) {
                std::cout << -1 << '\n';
            } else {
                std::cout << k + 1 << '\n';
                seg.set(k, {-1, k});
            }
        } else {
            auto f = [&](auto p) { return p.first <= x; };
            int k = seg.min_left(f);
            if (k == 0) {
                std::cout << -1 << '\n';
            } else {
                std::cout << k << '\n';
                seg.set(k - 1, {-1, k - 1});
            }
        }
    }

    return 0;
}
