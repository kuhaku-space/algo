// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/enumerate_palindromes
#include <iostream>
#include <string>
#include "string/manacher.hpp"
#include "template/vector.hpp"

int main(void) {
    std::string s;
    std::cin >> s;
    std::string t;
    for (auto c : s) {
        t += ' ';
        t += c;
    }
    t += ' ';

    Manacher ma(t);
    auto ans = ma.get();
    ans.erase(ans.begin());
    ans.pop_back();
    Dec >> ans;
    for (int i = 0; i < (int)ans.size(); ++i)
        std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');

    return 0;
}
