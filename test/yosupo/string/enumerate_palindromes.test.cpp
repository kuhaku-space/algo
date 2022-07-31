#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include "string/manacher.hpp"
#include "template/atcoder.hpp"

int main(void) {
    string s;
    cin >> s;
    string t;
    for (auto c : s) {
        t += ' ';
        t += c;
    }
    t += ' ';

    Manacher ma(t);
    auto ans = ma.get();
    ans.erase(ans.begin());
    ans.pop_back();
    for (auto &x : ans) {
        --x;
    }
    co(ans);

    return 0;
}
