#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
#include "string/suffix_array.hpp"
#include "template/atcoder.hpp"

int main(void) {
    string s;
    cin >> s;
    auto sa = suffix_array(s);
    auto v = lcp_array(s, sa);
    int n = s.size();
    ll ans = ll(n) * (n + 1) / 2;
    for (auto x : v) ans -= x;
    co(ans);

    return 0;
}
