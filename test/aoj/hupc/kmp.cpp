#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2763"
#include "string/kmp.hpp"
#include "template/atcoder.hpp"

int main(void) {
    string s;
    cin >> s;
    int n = s.size();
    int x = n - knuth_morris_pratt(s)[n];
    int y = n + 1;
    while (!(y % x == 0 && y / x % 3 == 0)) ++y;
    int b = y - n;
    if (b * 2 > n - 3) {
        co("mitomerarenaiWA");
        return 0;
    }
    string ans = "Love ";
    ans += s.substr(0, y / 3);
    ans += "!";
    co(ans);

    return 0;
}
