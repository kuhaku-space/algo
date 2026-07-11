// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
#include <iostream>
#include <utility>
#include "data_structure/lazy_dynamic_sequence.hpp"
#include "math/modint.hpp"

using Mint = modint998;

struct M1 {
    using T = std::pair<Mint, Mint>;
    using value_type = T;
    static constexpr T id() { return T(); }
    static constexpr T op(T lhs, T rhs) { return {lhs.first + rhs.first, rhs.second + lhs.second}; }
};

struct M2 {
    using T = std::pair<Mint, Mint>;
    using value_type = T;
    static constexpr T id() { return T(1, 0); }
    static constexpr T op(T lhs, T rhs) { return {lhs.first * rhs.first, lhs.first * rhs.second + lhs.second}; }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return {lhs.first * rhs.first + lhs.second * rhs.second, rhs.second};
    }
};

int main(void) {
    int n, q;
    std::cin >> n >> q;
    LazyDynamicSequence<M1, M2> seq;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        seq.push_back(std::pair<Mint, Mint>(a, 1));
    }
    while (q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int i, x;
            std::cin >> i >> x;
            seq.insert(i, std::pair<Mint, Mint>(x, 1));
        } else if (t == 1) {
            int i;
            std::cin >> i;
            seq.erase(i);
        } else if (t == 2) {
            int l, r;
            std::cin >> l >> r;
            seq.reverse(l, r);
        } else if (t == 3) {
            int l, r, b, c;
            std::cin >> l >> r >> b >> c;
            seq.apply(l, r, std::pair<Mint, Mint>(b, c));
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << seq.prod(l, r).first << '\n';
        }
    }

    return 0;
}
