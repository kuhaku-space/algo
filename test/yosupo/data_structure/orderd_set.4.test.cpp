// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/ordered_set
#include <iostream>
#include "binary_tree/splay_tree.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    splay_tree<int> tr;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        tr.insert(x);
    }
    while (q--) {
        int t, x;
        std::cin >> t >> x;
        if (t == 0) {
            if (!tr.contains(x)) tr.insert(x);
        } else if (t == 1) {
            tr.erase(x);
        } else if (t == 2) {
            if (tr.size() < x) std::cout << -1 << '\n';
            else std::cout << tr.get(x - 1) << '\n';
        } else if (t == 3) {
            std::cout << tr.upper_bound(x) << '\n';
        } else if (t == 4) {
            auto ans = tr.floor(x);
            if (ans) std::cout << ans.value() << '\n';
            else std::cout << -1 << '\n';
        } else {
            auto ans = tr.ceil(x);
            if (ans) std::cout << ans.value() << '\n';
            else std::cout << -1 << '\n';
        }
    }

    return 0;
}
