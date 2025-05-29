// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/longest_common_substring
#include <iostream>
#include <string>
#include "string/suffix_array.hpp"

int main(void) {
    std::string s, t;
    std::cin >> s >> t;
    int n = s.size(), m = t.size();
    auto is_s = [&](int x) { return 0 <= x && x < n; };
    auto is_t = [&](int x) { return n + 1 <= x && x < n + m + 1; };
    std::string st = s + "_" + t;
    auto sa = suffix_array(st);
    auto v = lcp_array(st, sa);
    int ans = 0, a = 0, b = 0;
    for (int i = 0; i < (int)sa.size() - 1; ++i) {
        if (is_s(sa[i]) && is_t(sa[i + 1]) && ans < v[i]) {
            ans = v[i];
            a = sa[i], b = sa[i + 1] - n - 1;
        }
        if (is_t(sa[i]) && is_s(sa[i + 1]) && ans < v[i]) {
            ans = v[i];
            a = sa[i + 1], b = sa[i] - n - 1;
        }
    }
    std::cout << a << ' ' << a + ans << ' ' << b << ' ' << b + ans << '\n';

    return 0;
}
