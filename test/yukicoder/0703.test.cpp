// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/703
#include <cstdint>
#include <iostream>
#include <vector>
#include "dp/cht.hpp"

int main(void) {
    int n;
    std::cin >> n;
    std::vector<std::int64_t> a(n), x(n), y(n);
    for (auto &v : a) std::cin >> v;
    for (auto &v : x) std::cin >> v;
    for (auto &v : y) std::cin >> v;

    // dp[i] = (a_i - x_j)^2 + y_j^2 + dp[j-1] の最小化
    //       = a_i^2 + min_j ( (-2 x_j) a_i + (x_j^2 + y_j^2 + dp[j-1]) )
    // 傾き -2 x_j は x の昇順より単調減少 → 最小値用 CHT
    cht<std::int64_t> ch;
    auto sq = [](std::int64_t v) { return v * v; };
    std::vector<std::int64_t> dp(n);
    for (int i = 0; i < n; ++i) {
        std::int64_t prev = (i == 0 ? 0 : dp[i - 1]);
        ch.add(-2 * x[i], sq(x[i]) + sq(y[i]) + prev);
        dp[i] = ch.get(a[i]) + sq(a[i]);
    }
    std::cout << dp[n - 1] << '\n';
    return 0;
}
