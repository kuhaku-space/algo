// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_D
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "algorithm/binary_search.hpp"
#include "segtree/monoid.hpp"
#include "sparse_table/linear_sparse_table.hpp"
#include "string/suffix_array.hpp"

// suffix array 上を t との直接比較で二分探索する素直な版。
bool contains_naive(const std::string &s, const std::vector<int> &v, const std::string &t) {
    int n = s.size();
    int l = -1, r = n - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (s.substr(v[m], t.size()) < t) l = m;
        else r = m;
    }
    return s.substr(v[r], t.size()) == t;
}

// LCP 配列 + スパーステーブルで一致済み長さを使い回しながら二分探索する版。
bool contains_lcp(const std::string &s, const std::vector<int> &v, const linear_sparse_table<Min<int>> &st,
                  const std::string &t) {
    int n = s.size();
    int l = 0, x = 0;
    auto f = [&](int m) {
        if (st.prod(l, m + 1) > x) {
            l = m + 1;
            return false;
        }
        if (st.prod(l, m + 1) == x) {
            for (int i = x; i < (int)t.size(); ++i) {
                if (v[m] + i == (int)s.size() || s[v[m] + i] < t[i]) {
                    x = i;
                    l = m + 1;
                    return false;
                } else if (s[v[m] + i] > t[i]) {
                    return true;
                }
            }
        }
        return true;
    };
    int ans = meguru_binary_search(n - 1, -1, f);
    return s.substr(v[ans], t.size()) == t;
}

int main(void) {
    std::string s;
    std::cin >> s;
    auto v = suffix_array(s);
    auto lcp = lcp_array(s, v);
    lcp.emplace(lcp.begin(), 0);
    linear_sparse_table<Min<int>> st(lcp);

    int q;
    std::cin >> q;
    while (q--) {
        std::string t;
        std::cin >> t;
        bool ans_naive = contains_naive(s, v, t);
        bool ans_lcp = contains_lcp(s, v, st, t);
        assert(ans_naive == ans_lcp);
        std::cout << ans_naive << '\n';
    }

    return 0;
}
