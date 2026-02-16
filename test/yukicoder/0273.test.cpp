// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/273
#include <iostream>
#include <string>
#include "algorithm/palindrome.hpp"

int main(void) {
    std::string s;
    std::cin >> s;
    int n = s.size();
    int ans = 0;
    for (int l = 1; l < n; ++l) {
        for (int i = 0; i <= n - l; ++i) {
            if (is_palindrome(s.substr(i, l))) ans = std::max(ans, l);
        }
    }
    std::cout << ans << '\n';

    return 0;
}
