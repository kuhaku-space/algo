// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/ordered_set
#include <cassert>
#include <iostream>
#include <vector>
#include "ordered_set/binary_trie.hpp"
#include "ordered_set/ordered_set.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    OrderedSet<int> os(a);
    binary_trie<int> bt;
    for (int e : a) bt.insert(e);
    while (q--) {
        int t, x;
        std::cin >> t >> x;
        if (t == 0) {
            os.insert(x);
            bt.insert(x);
        } else if (t == 1) {
            os.erase(x);
            bt.erase(x);
        } else if (t == 2) {
            bool none_os = os.size() < x;
            bool none_bt = bt.size() < x;
            assert(none_os == none_bt);
            if (none_os) {
                std::cout << -1 << '\n';
            } else {
                int ans_os = os.at(x - 1);
                int ans_bt = bt.get(x - 1);
                assert(ans_os == ans_bt);
                std::cout << ans_os << '\n';
            }
        } else if (t == 3) {
            int ans_os = os.upper_bound(x);
            int ans_bt = bt.upper_bound(x);
            assert(ans_os == ans_bt);
            std::cout << ans_os << '\n';
        } else if (t == 4) {
            auto ans_os = os.floor(x);
            auto ans_bt = bt.floor(x);
            assert(ans_os == ans_bt);
            if (ans_os) std::cout << ans_os.value() << '\n';
            else std::cout << -1 << '\n';
        } else {
            auto ans_os = os.ceil(x);
            auto ans_bt = bt.ceil(x);
            assert(ans_os == ans_bt);
            if (ans_os) std::cout << ans_os.value() << '\n';
            else std::cout << -1 << '\n';
        }
    }

    return 0;
}
