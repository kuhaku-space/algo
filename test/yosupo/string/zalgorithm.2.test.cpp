// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/zalgorithm
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include "string/rolling_hash.hpp"

int main(void) {
    std::string s;
    std::cin >> s;

    rolling_hash rh(s);
    int n = s.size();
    std::vector<int> ans = {n};
    std::unordered_set<uint64_t> st;
    for (int i = 1; i <= n; ++i) st.emplace(rh.get(0, i));
    for (int i = 1; i < n; ++i) {
        int l = 0, r = n - i + 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (st.count(rh.get(i, i + m))) l = m;
            else r = m;
        }
        ans.emplace_back(l);
    }
    for (int i = 0; i < (int)ans.size(); ++i)
        std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');

    return 0;
}
