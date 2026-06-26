// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/sum_of_multiplicative_function_large
#include <iostream>
#include <utility>
#include <vector>
#include "math/modint.hpp"
#include "number_theory/min25_sieve.hpp"

// f は f(p^e) = a*e + b*p を満たす乗法的関数。f(p) = a + b*p。
using Mint = static_modint<469762049>;

int main() {
    int t;
    std::cin >> t;
    const Mint inv2 = Mint(1) / Mint(2);
    while (t--) {
        long long n, a, b;
        std::cin >> n >> a >> b;
        std::vector<Min25Term<Mint>> terms = {
            {Mint(a), 0, [](long long x) { return Mint(x); }},
            {Mint(b), 1, [inv2](long long x) { return Mint(x) * Mint(x + 1) * inv2; }},
        };
        auto fpe = [a, b](long long p, int e, long long) { return Mint(a) * Mint(e) + Mint(b) * Mint(p); };
        std::cout << min25_sum<Mint>(n, std::move(terms), fpe) << '\n';
    }
    return 0;
}
