#define PROBLEM "https://yukicoder.me/problems/no/0263"
#include "template/atcoder.hpp"
#include "tree/palindromic_tree.hpp"

int main(void) {
    std::string s, t;
    std::cin >> s >> t;
    palindromic_tree pt;
    for (auto c : s) pt.add(c);
    auto v = pt.build_frequency();
    std::vector<ll> vs(all(v));
    int m = vs.size();
    rep (i, m) {
        if (i < 2) continue;
        int p = pt.get_node(i)->suffix_link;
        if (p >= 2) vs[i] += vs[p];
    }
    pt.clear();
    ll ans = 0;
    for (auto c : t) {
        int idx = pt.move(c);
        if (idx >= 2) ans += vs[idx];
    }
    co(ans);

    return 0;
}
