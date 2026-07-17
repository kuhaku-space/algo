// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2444
#include "string/rolling_hash.hpp"
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_set>

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::string s, t;
    std::cin >> s;
    rolling_hash rh(s);
    int l = 0, r = 1;
    std::unordered_set<std::uint64_t> st;
    while (q--) {
        std::cin >> t;
        if (t == "L++") ++l;
        else if (t == "L--") --l;
        else if (t == "R++") ++r;
        else --r;
        st.emplace(rh.get(l, r));
    }
    std::cout << st.size() << '\n';

    return 0;
}
