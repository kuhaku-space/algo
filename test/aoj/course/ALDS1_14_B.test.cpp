// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "string/kmp.hpp"
#include "string/rolling_hash.hpp"

int main(void) {
    std::string s, t;
    std::cin >> s >> t;

    knuth_morris_pratt kmp(t);
    auto match = kmp.search(s);
    std::vector<int> pos_kmp;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (match[i] == (int)t.size()) pos_kmp.emplace_back(i - (int)t.size() + 1);
    }

    rolling_hash rh(s);
    auto pos_hash = rh.search(t);

    assert(pos_kmp == pos_hash);
    for (auto e : pos_kmp) std::cout << e << '\n';

    return 0;
}
