// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/suffixarray
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include "string/rolling_hash.hpp"

int main(void) {
    std::string s;
    std::cin >> s;
    int n = s.size();
    s += "$";
    rolling_hash rh(s);

    std::vector<int> ord(n);
    std::iota(ord.begin(), ord.end(), 0);
    std::sort(ord.begin(), ord.end(), [&](int x, int y) {
        int l = 0, r = n - std::max(x, y) + 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            auto h1 = rh.substr(x, m);
            auto h2 = rh.substr(y, m);
            if (h1 == h2) l = m;
            else r = m;
        }

        return s[x + l] < s[y + l];
    });

    for (int i = 0; i < (int)ord.size(); ++i)
        std::cout << ord[i] << (i == (int)ord.size() - 1 ? '\n' : ' ');

    return 0;
}
