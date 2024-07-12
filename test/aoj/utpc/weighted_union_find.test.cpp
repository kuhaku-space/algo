// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2207
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>

#include "tree/weighted_union_find.hpp"

std::tuple<std::string, std::string, int> input() {
    int tmp, x;
    std::string s, t;
    char c;
    std::cin >> tmp >> s >> c >> tmp >> c >> x >> t;
    return std::make_tuple(s, t, x);
}

int main(void) {
    while (true) {
        int n;
        std::cin >> n;
        if (!n)
            break;
        std::unordered_map<std::string, int> mp;
        int len = 0;
        weighted_union_find<int> uf(n * 2);
        bool ans = true;
        while (n--) {
            auto [s, t, x] = input();
            if (!mp.count(s))
                mp[s] = len++;
            if (!mp.count(t))
                mp[t] = len++;
            if (uf.same(mp[s], mp[t])) {
                if (uf.diff(mp[s], mp[t]) != x) {
                    ans = false;
                }
            } else {
                uf.unite(mp[s], mp[t], x);
            }
        }
        std::cout << (ans ? "Yes" : "No") << '\n';
    }

    return 0;
}
