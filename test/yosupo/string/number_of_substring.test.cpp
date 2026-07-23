// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/number_of_substrings
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include "string/suffix_array.hpp"
#include "string/suffix_automaton.hpp"
#include "string/suffix_tree.hpp"

int main(void) {
    std::string s;
    std::cin >> s;
    int n = s.size();

    std::int64_t ans_sa = std::int64_t(n) * (n + 1) / 2;
    {
        auto sa = suffix_array(s);
        auto lcp = lcp_array(s, sa);
        for (auto x : lcp) ans_sa -= x;
    }

    std::int64_t ans_tree = 0;
    {
        suffix_tree<char> st(s);
        for (std::size_t i = 1; i < st.nodes.size(); ++i) ans_tree += st.nodes[i].len();
    }

    std::int64_t ans_sam = 0;
    {
        suffix_automaton<char> sam(s);
        for (int i = 1; i < sam.size(); ++i) ans_sam += sam.nodes[i].len - sam.nodes[sam.nodes[i].link].len;
    }

    std::int64_t ans_ssam = 0;
    {
        string_suffix_automaton<> ssam(s);
        for (int i = 1; i < ssam.size(); ++i) ans_ssam += ssam.nodes[i].len - ssam.nodes[ssam.nodes[i].link].len;
    }

    assert(ans_sa == ans_tree);
    assert(ans_sa == ans_sam);
    assert(ans_sa == ans_ssam);
    std::cout << ans_sa << '\n';

    return 0;
}
