// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/kth_root_integer
#include <cmath>
#include <iostream>
#include "algorithm/binary_search.hpp"

int main(void) {
    int q;
    std::cin >> q;
    while (q--) {
        std::uint64_t a, k;
        std::cin >> a >> k;
        if (a == 0 || a == 1 || k == 1) {
            std::cout << a << '\n';
            continue;
        }
        if (k == 64) {
            std::cout << 1 << '\n';
            continue;
        }
        if (k >= 41) {
            if (a >= (1ul << k)) std::cout << 2 << '\n';
            else std::cout << 1 << '\n';
            continue;
        }
        if (k == 2) {
            std::cout << (std::uint64_t)sqrtl(a) << '\n';
            continue;
        }
        auto f = [&](std::uint64_t x) {
            __uint128_t q = 1;
            for (int i = 0; i < k; ++i) {
                q *= x;
                if (q > a) break;
            }
            return q <= a;
        };
        std::cout << meguru_binary_search(1, 2642246, f) << '\n';
    }

    return 0;
}
