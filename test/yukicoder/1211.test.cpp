#define PROBLEM "https://yukicoder.me/problems/no/1211"
#include <cstdint>
#include <iostream>
#include <vector>
#include "graph/functional_graph.hpp"

int main(void) {
    int n, k;
    std::cin >> n >> k;
    std::vector<std::int64_t> a(n);
    for (auto &e : a) std::cin >> e;
    auto b = a;
    b.insert(b.begin(), 0);
    b.insert(b.end(), a.begin(), a.end());
    for (int i = 0; i < n * 2; ++i) b[i + 1] += b[i];
    std::int64_t l = 1, r = b[n] / k + 1;
    std::vector<int> to(n * 2 + 2, n * 2 + 1);
    while (r - l > 1) {
        std::int64_t m = (l + r) / 2;
        int idx = 0;
        for (int i = 0; i < n * 2; ++i) {
            while (idx < (int)b.size() && b[idx] - b[i] < m) ++idx;
            to[i] = idx;
        }
        functional_graph fg(to);
        auto v = fg.jump_all(k);
        bool f = false;
        for (int i = 0; i < n; ++i) {
            if (v[i] - i <= n) {
                f = true;
                break;
            }
        }
        (f ? l : r) = m;
    }
    std::cout << l << '\n';

    return 0;
}
