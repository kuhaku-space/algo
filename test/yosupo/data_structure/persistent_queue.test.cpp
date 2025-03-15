// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/persistent_queue
#include "persistent_ds/persistent_queue.hpp"
#include <iostream>
#include <vector>

int main(void) {
    int q;
    std::cin >> q;
    std::vector<persistent_queue<int>> qs;
    qs.emplace_back();
    while (q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int k, x;
            std::cin >> k >> x;
            qs.emplace_back(qs[k + 1].emplace(x));
        } else {
            int k;
            std::cin >> k;
            std::cout << qs[k + 1].top() << '\n';
            qs.emplace_back(qs[k + 1].pop());
        }
    }

    return 0;
}
