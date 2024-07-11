// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/cartesian_tree
#include "tree/cartesian_tree.hpp"
#include <iostream>
#include <vector>

int main(void) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    auto ans = cartesian_tree(a);
    for (int i = 0; i < n; ++i) {
        if (ans[i] == -1) ans[i] = i;
    }
    for (int i = 0; i < (int)ans.size(); ++i)
        std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');

    return 0;
}
