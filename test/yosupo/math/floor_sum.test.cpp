// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/sum_of_floor_of_linear
#include "math/floor_sum.hpp"
#include <iostream>

int main(void) {
    int t;
    std::cin >> t;
    while (t--) {
        int n, m, a, b;
        std::cin >> n >> m >> a >> b;
        std::cout << floor_sum(n, m, a, b) << '\n';
    }

    return 0;
}
