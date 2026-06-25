// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/952
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>
#include "dp/cht.hpp"

// k 個の扉を開けたときの危険度（連続して開いた扉の和の二乗の総和）の最小値を
// k = 1..N について求める。仮想的な仕切りを位置 0 と N+1 に置くと、
// 仕切りを t 個使った dp は
//   dp[t][i] = min_{l < i} dp[t-1][l] + (S[i-1] - S[l])^2
//            = S[i-1]^2 + min_l ( (-2 S[l]) S[i-1] + (dp[t-1][l] + S[l]^2) )
// となる。S は単調増加なので傾き -2 S[l] は単調減少 → 最小値用の単調 CHT。
int main(void) {
    int n;
    std::cin >> n;
    std::vector<std::int64_t> s(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        std::int64_t a;
        std::cin >> a;
        s[i] = s[i - 1] + a;
    }

    const std::int64_t inf = static_cast<std::int64_t>(4e18);
    std::vector<std::int64_t> prev(n + 2, inf), ans(n + 1, inf);
    prev[0] = 0;
    for (int t = 1; t <= n; ++t) {
        std::vector<std::int64_t> cur(n + 2, inf);
        cht<std::int64_t> ch;
        int l = 0;
        for (int i = t; i <= n + 1; ++i) {
            while (l <= i - 1) {
                if (prev[l] < inf) ch.add(-2 * s[l], prev[l] + s[l] * s[l]);
                ++l;
            }
            if (!ch.empty()) cur[i] = ch.get(s[i - 1]) + s[i - 1] * s[i - 1];
        }
        // 仕切り t 個 → 閉じた扉 t-1 個 → 開けた扉 k = N-(t-1)
        ans[n - (t - 1)] = cur[n + 1];
        prev = std::move(cur);
    }

    for (int k = 1; k <= n; ++k) std::cout << ans[k] << '\n';
    return 0;
}
