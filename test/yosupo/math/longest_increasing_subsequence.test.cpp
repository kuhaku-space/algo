// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/longest_increasing_subsequence
#include <iostream>
#include <vector>
#include "algorithm/lis.hpp"

int main(void) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    auto ans = make_lis(a);
    std::cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i)
        std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');

    return 0;
}
