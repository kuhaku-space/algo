// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2863
#include "string/rolling_hash.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include "math/modint.hpp"

using Mint = modint107;

int main(void) {
    int m;
    std::cin >> m;
    rolling_hash rh;
    std::unordered_set<std::uint64_t> st;
    std::vector<int> lens;
    std::string t;
    for (int i = 0; i < m; ++i) {
        std::cin >> t;
        st.emplace(rh.hash(t));
        lens.emplace_back(t.size());
    }
    std::sort(lens.begin(), lens.end());
    lens.erase(std::unique(lens.begin(), lens.end()), lens.end());
    std::string s;
    std::cin >> s;
    rolling_hash rhs(s, rh.get_base());
    int n = s.size();
    std::vector<Mint> dp(n + 1);
    dp[0] = 1;
    for (int i = 1; i < n + 1; ++i) {
        for (int x : lens) {
            if (i < x) break;
            if (st.count(rhs.get(i - x, i))) dp[i] += dp[i - x];
        }
    }
    std::cout << dp.back() << '\n';

    return 0;
}
