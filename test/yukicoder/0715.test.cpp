// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/715
#include <algorithm>
#include <iostream>
#include <vector>
#include "algorithm/mex.hpp"

int main(void) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int &e : a) std::cin >> e;

    std::vector<int> dp = {0, 1};
    for (int x = 2; x < 400; ++x) {
        minimum_excluded mex;
        mex.add(dp[x - 2]);
        for (int i = 0; i < x - 2; ++i) mex.add(dp[i] ^ dp[x - i - 3]);
        dp.emplace_back(mex());
    }

    int c = 0;
    std::sort(a.begin(), a.end());
    int x = a.front();
    int ans = 0;
    for (int e : a) {
        if (e == x + c) {
            ++c;
            continue;
        }
        if (c >= 340) ans ^= dp[340 + c % 34];
        else ans ^= dp[c];
        c = 1;
        x = e;
    }
    if (c >= 340) ans ^= dp[340 + c % 34];
    else ans ^= dp[c];

    if (ans) std::cout << "First\n";
    else std::cout << "Second\n";

    return 0;
}
