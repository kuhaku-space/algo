#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"
#include "binary_tree/patricia_binary_trie.hpp"
#include <iostream>

int main(void) {
    int q;
    std::cin >> q;
    patricia_binary_trie<int, 30> bt;
    while (q--) {
        int t, x;
        std::cin >> t >> x;
        if (t == 0) bt.insert(x);
        else if (t == 1) bt.erase(x);
        else std::cout << (bt.min_element(x) ^ x) << '\n';
    }

    return 0;
}
