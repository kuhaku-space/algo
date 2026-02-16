// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/0263
#include <cstdint>
#include <iostream>
#include <string>
#include "tree/palindromic_tree.hpp"

int main(void) {
    std::string s, t;
    std::cin >> s >> t;
    palindromic_tree pt;
    for (auto c : s) pt.add(c);
    auto v = pt.build_frequency();
    std::vector<std::int64_t> vs(v.begin(), v.end());
    int m = vs.size();
    for (int i = 0; i < m; ++i) {
        if (i < 2) continue;
        int p = pt.get_node(i)->suffix_link;
        if (p >= 2) vs[i] += vs[p];
    }
    pt.clear();
    std::int64_t ans = 0;
    for (auto c : t) {
        int idx = pt.move(c);
        if (idx >= 2) ans += vs[idx];
    }
    std::cout << ans << '\n';

    return 0;
}
