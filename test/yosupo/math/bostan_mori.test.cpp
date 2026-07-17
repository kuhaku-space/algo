// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence
#include "math/bostan_mori.hpp"
#include <iostream>
#include <vector>
#include "math/modint.hpp"

using Mint = modint998;

int main() {
    int d;
    std::uint64_t k;
    std::cin >> d >> k;
    std::vector<Mint> a(d), c(d);
    for (int i = 0; i < d; ++i) std::cin >> a[i];
    for (int i = 0; i < d; ++i) std::cin >> c[i];
    std::cout << kth_term(a, c, k) << std::endl;
    return 0;
}
