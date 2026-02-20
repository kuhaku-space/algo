// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/number_of_substrings
#include <cstdint>
#include <iostream>
#include <string>
#include "string/suffix_automaton.hpp"

int main(void) {
    std::string s;
    std::cin >> s;

    string_suffix_automaton<> sa(s);
    std::int64_t ans = 0;
    for (int i = 1; i < sa.size(); ++i) {
        ans += sa.nodes[i].len - sa.nodes[sa.nodes[i].link].len;
    }
    std::cout << ans << '\n';

    return 0;
}
