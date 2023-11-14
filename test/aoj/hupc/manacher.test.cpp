#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2934"
#include "string/manacher.hpp"
#include <iostream>
#include <string>

int solve(const std::string &s) {
    int n = s.size();
    if (n == 1) return 1;
    Manacher manacher(s);
    for (int m = 1; m < n; ++m) {
        bool flag = true;
        int k = m;
        while (k < n) {
            flag &= manacher[k] >= std::min(m + 1, n - k);
            k += m;
        }
        if (flag) return m + 1;
    }
    return n;
}

int main(void) {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::cout << solve(s) << std::endl;

    return 0;
}
