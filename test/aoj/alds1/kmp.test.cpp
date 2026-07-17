// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B
#include "string/kmp.hpp"
#include <iostream>
#include <string>

int main(void) {
    std::string s, t;
    std::cin >> s >> t;
    knuth_morris_pratt kmp(t);
    auto ans = kmp.search(s);
    for (int i = 0; i < (int)s.size(); ++i) {
        if (ans[i] == (int)t.size()) std::cout << i - t.size() + 1 << '\n';
    }

    return 0;
}
