// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_D
#include "string/suffix_array.hpp"
#include <iostream>
#include <string>

int main(void) {
    std::string s;
    std::cin >> s;
    int n = s.size();
    auto v = suffix_array(s);
    int q;
    std::cin >> q;
    while (q--) {
        std::string t;
        std::cin >> t;
        int l = -1, r = n - 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (s.substr(v[m], t.size()) < t) l = m;
            else r = m;
        }
        std::cout << (s.substr(v[r], t.size()) == t) << std::endl;
    }

    return 0;
}
