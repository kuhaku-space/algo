#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"
#include "binary_tree/patricia_binary_trie.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int q;
    cin >> q;
    patricia_binary_trie<int, 30> bt;
    while (q--) {
        int t, x;
        cin >> t >> x;
        if (t == 0) bt.insert(x);
        else if (t == 1) bt.erase(x);
        else co(bt.min_element(x) ^ x);
    }

    return 0;
}
