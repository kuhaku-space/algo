#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
#include <cstdint>
#include <iostream>
#include <vector>
#include "string/suffix_array.hpp"

int main(void) {
    std::string s;
    std::cin >> s;
    auto sa = suffix_array(s);
    auto v = lcp_array(s, sa);
    int n = s.size();
    std::int64_t ans = std::int64_t(n) * (n + 1) / 2;
    for (auto x : v) ans -= x;
    std::cout << ans << '\n';

    return 0;
}
