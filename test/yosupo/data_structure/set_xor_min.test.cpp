// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/set_xor_min
#include <cassert>
#include <iostream>
#include "ordered_set/binary_trie.hpp"
#include "ordered_set/patricia_binary_trie.hpp"

int main(void) {
    int q;
    std::cin >> q;
    binary_trie<int, 30> bt;
    patricia_binary_trie<int, 30> pbt;
    while (q--) {
        int t, x;
        std::cin >> t >> x;
        if (t == 0) {
            bt.insert(x);
            pbt.insert(x);
        } else if (t == 1) {
            bt.erase(x);
            pbt.erase(x);
        } else {
            int ans_bt = bt.min_element(x) ^ x;
            int ans_pbt = pbt.min_element(x) ^ x;
            assert(ans_bt == ans_pbt);
            std::cout << ans_bt << '\n';
        }
    }

    return 0;
}
