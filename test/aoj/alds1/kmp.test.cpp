#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B"
#include "string/kmp.hpp"
#include "template/atcoder.hpp"

int main(void) {
    string s, t;
    cin >> s >> t;
    KMP<string> kmp(t);
    auto ans = kmp.search(s);
    rep(i, s.size()) {
        if (ans[i] == t.size()) {
            co(i - t.size() + 1);
        }
    }

    return 0;
}
