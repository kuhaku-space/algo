// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/2606
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include "string/palindromic_tree.hpp"

int main() {
    std::string s;
    std::cin >> s;

    palindromic_tree pt;
    for (char c : s) pt.add(c);
    auto freq = pt.build_frequency();  // 各回文の S 中出現回数

    int m = pt.size();
    // 回文 v まで作るスコア = suffix link 先（最長真回文接頭辞）までのスコア + len*出現回数
    std::vector<std::int64_t> dp(m, 0);
    std::int64_t ans = 0;
    for (int i = 2; i < m; ++i) {
        auto *nd = pt.get_node(i);
        dp[i] = dp[nd->suffix_link] + std::int64_t(nd->len) * freq[i];
        ans = std::max(ans, dp[i]);
    }
    std::cout << ans << '\n';
    return 0;
}
