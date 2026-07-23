// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2863
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include "math/modint.hpp"
#include "string/aho_corasick.hpp"
#include "string/rolling_hash.hpp"
#include "tree/tree_function.hpp"

using Mint = modint107;

// ローリングハッシュで単語集合をハッシュ集合として持ち、部分文字列一致を判定する版。
Mint solve_rolling_hash(int m, const std::vector<std::string> &t, const std::string &s) {
    rolling_hash rh;
    std::unordered_set<std::uint64_t> st;
    std::vector<int> lens;
    for (int i = 0; i < m; ++i) {
        st.emplace(rh.hash(t[i]));
        lens.emplace_back(t[i].size());
    }
    std::sort(lens.begin(), lens.end());
    lens.erase(std::unique(lens.begin(), lens.end()), lens.end());
    rolling_hash rhs(s, rh.get_base());
    int n = s.size();
    std::vector<Mint> dp(n + 1);
    dp[0] = 1;
    for (int i = 1; i < n + 1; ++i) {
        for (int x : lens) {
            if (i < x) break;
            if (st.count(rhs.get(i - x, i))) dp[i] += dp[i - x];
        }
    }
    return dp.back();
}

// Aho-Corasick オートマトンで単語集合を管理し、fail 木を遡って一致した単語を列挙する版。
Mint solve_aho_corasick(int m, const std::vector<std::string> &t, const std::string &s) {
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
    int n = s.size();
    auto res = aho.search(s);
    std::vector<Mint> dp(n + 1);
    dp[0] = 1;
    for (int i = 0; i < n + 1; ++i) {
        for (auto y : correct[res[i]]) dp[i] += dp[i - t[y].size()];
    }
    return dp.back();
}

int main(void) {
    int m;
    std::cin >> m;
    std::vector<std::string> t(m);
    for (auto &e : t) std::cin >> e;
    std::string s;
    std::cin >> s;

    Mint ans_hash = solve_rolling_hash(m, t, s);
    Mint ans_aho = solve_aho_corasick(m, t, s);
    assert(ans_hash == ans_aho);
    std::cout << ans_hash << '\n';

    return 0;
}
