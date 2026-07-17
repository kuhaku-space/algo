// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/factorize
#include "math/factorize.hpp"
#include <cstdint>
#include <iostream>

int main(void) {
    int q;
    std::cin >> q;
    while (q--) {
        std::int64_t x;
        std::cin >> x;
        auto v = factorize(x);
        std::cout << v.size();
        for (auto e : v) std::cout << ' ' << e;
        std::cout << '\n';
    }

    return 0;
}
