#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Regional/2863?year=2017"
#include "string/aho_corasick.hpp"
#include "math/modint.hpp"
#include "template/atcoder.hpp"
#include "tree/tree_function.hpp"

using Mint = ModInt<MOD>;

int main(void) {
    int m;
    cin >> m;
    vector<string> t(m);
    cin >> t;
    aho_corasick<26, 'a'> aho;
    vector<vector<int>> correct;
    rep (i, m) {
        auto v = aho.insert(t[i]);
        correct.resize(aho.size());
        correct[v.back()].emplace_back(i);
    }
    auto failure = aho.build();
    auto bfs = tree_bfs(failure);
    for (auto x : bfs) {
        int y = failure[x];
        vector<int> v;
        set_union(correct[x].begin(), correct[x].end(), correct[y].begin(), correct[y].end(),
                  back_inserter(v));
        correct[x] = v;
    }
    string s;
    cin >> s;
    int n = s.size();
    auto res = aho.search(s);
    vector<Mint> dp(n + 1);
    dp[0] = 1;
    rep (i, n + 1) {
        for (auto y : correct[res[i]]) {
            dp[i] += dp[i - t[y].size()];
        }
    }
    co(dp[n]);

    return 0;
}
