// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2863
#include "string/aho_corasick.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include "math/modint.hpp"
#include "tree/tree_function.hpp"

using Mint = modint107;

int main(void) {
    int m;
    std::cin >> m;
    std::vector<std::string> t(m);
    std::copy_n(std::istream_iterator<std::string>(std::cin), m, t.begin());
    aho_corasick<26, 'a'> aho;
    std::vector<std::vector<int>> correct;
    for (int i = 0; i < m; ++i) {
        auto v = aho.insert(t[i]);
        correct.resize(aho.size());
        correct[v.back()].emplace_back(i);
    }
    aho.build();
    auto failure = aho.failures();
    auto bfs = tree_bfs(failure);
    for (auto x : bfs) {
        int y = failure[x];
        std::vector<int> v;
        std::set_union(correct[x].begin(), correct[x].end(), correct[y].begin(), correct[y].end(),
                       std::back_inserter(v));
        correct[x] = v;
    }
    std::string s;
    std::cin >> s;
    int n = s.size();
    auto res = aho.search(s);
    std::vector<Mint> dp(n + 1);
    dp[0] = 1;
    for (int i = 0; i < n + 1; ++i) {
        for (auto y : correct[res[i]]) dp[i] += dp[i - t[y].size()];
    }
    std::cout << dp.back() << std::endl;

    return 0;
}
