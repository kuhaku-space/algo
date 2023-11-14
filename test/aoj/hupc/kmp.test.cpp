#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2763"
#include "string/kmp.hpp"
#include <iostream>
#include <string>

std::string solve(const std::string &s) {
    int n = s.size();
    int x = n - knuth_morris_pratt(s)[n];
    int y = n + 1;
    while (!(y % x == 0 && y / x % 3 == 0)) ++y;
    int b = y - n;
    if (b * 2 > n - 3) return "mitomerarenaiWA";
    return "Love " + s.substr(0, y / 3) + "!";
}

int main(void) {
    std::string s;
    std::cin >> s;
    std::cout << solve(s) << std::endl;

    return 0;
}
