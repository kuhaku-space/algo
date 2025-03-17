// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_D
#include <iostream>
#include <string>
#include "algorithm/binary_search.hpp"
#include "data_structure/linear_sparse_table.hpp"
#include "string/suffix_array.hpp"

template <class T>
struct Min {
    using value_type = T;
    static constexpr T id() { return std::numeric_limits<T>::max(); }
    static constexpr T op(const T &lhs, const T &rhs) { return std::min(lhs, rhs); }
};

int main(void) {
    std::string s;
    std::cin >> s;
    int n = s.size();
    auto v = suffix_array(s);
    auto lcp = lcp_array(s, v);
    lcp.emplace(lcp.begin(), 0);
    linear_sparse_table<Min<int>> st(lcp);
    int q;
    std::cin >> q;
    while (q--) {
        std::string t;
        std::cin >> t;
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
        std::cout << (s.substr(v[ans], t.size()) == t) << '\n';
    }

    return 0;
}
