// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/suffixarray
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include "string/rolling_hash.hpp"
#include "string/suffix_array.hpp"

int main(void) {
    std::string s;
    std::cin >> s;
    int n = s.size();

    auto sa = suffix_array(s);

    std::string s2 = s + "$";
    rolling_hash rh(s2);
    std::vector<int> ord(n);
    std::iota(ord.begin(), ord.end(), 0);
    std::sort(ord.begin(), ord.end(), [&](int x, int y) {
        int l = 0, r = n - std::max(x, y) + 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (rh.substr(x, m) == rh.substr(y, m)) l = m;
            else r = m;
        }
        return s2[x + l] < s2[y + l];
    });

    assert(sa == ord);
    for (int i = 0; i < n; ++i) std::cout << sa[i] << (i == n - 1 ? '\n' : ' ');

    return 0;
}
