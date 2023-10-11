#define PROBLEM "https://judge.yosupo.jp/problem/min_of_mod_of_linear"
#include "math/min_linear.hpp"
#include <iostream>

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        int n, m, a, b;
        std::cin >> n >> m >> a >> b;
        std::cout << min_linear(n, m, a, b) << '\n';
    }

    return 0;
}
