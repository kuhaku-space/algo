// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/number_of_subsequences
#include <algorithm>
#include <iostream>
#include <vector>
#include "algorithm/compress.hpp"
#include "math/modint.hpp"

using Mint = modint998;

int main(void) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    a = compress(a);
    Mint ans = 0;
    std::vector<Mint> dp(*std::max_element(a.begin(), a.end()) + 1);
    for (auto x : a) {
        auto t = ans - dp[x] + 1;
        ans += t, dp[x] += t;
    }
    std::cout << ans << '\n';

    return 0;
}
