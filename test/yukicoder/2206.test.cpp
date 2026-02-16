// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/2206
#include <iostream>
#include <utility>
#include <vector>
#include "algorithm/offline_binomial_sum.hpp"
#include "math/modint.hpp"

using Mint = modint998;

int main(void) {
    int q;
    std::cin >> q;
    std::vector<std::pair<int, int>> a(q);
    for (int i = 0; i < q; ++i) {
        int n, k;
        std::cin >> n >> k;
        a[i] = {n - 1, k - 1};
    }
    auto ans = offline_binomial_sum(a);
    for (int i = 0; i < q; ++i) ans[i] *= Mint(2).pow(a[i].first + 1) - 1;
    for (int i = 0; i < q; ++i) std::cout << ans[i] << '\n';
    return 0;
}
