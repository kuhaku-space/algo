// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_reverse_range_sum
#include <iostream>
#include "data_structure/dynamic_sequence.hpp"
#include "segtree/monoid.hpp"
#include "template/sonic.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    DynamicSequence<Add<long long>> seq;
    for (int i = 0; i < n; ++i) {
        long long a;
        std::cin >> a;
        seq.push_back(a);
    }
    while (q--) {
        int t, l, r;
        std::cin >> t >> l >> r;
        if (t == 0) seq.reverse(l, r);
        else std::cout << seq.prod(l, r) << '\n';
    }

    return 0;
}
