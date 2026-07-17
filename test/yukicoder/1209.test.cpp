// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1209
#include <iostream>
#include <vector>
#include "algorithm/inversion_number.hpp"

int main(void) {
    int n;
    std::cin >> n;
    std::vector<int> a(n), b(n);
    for (auto &e : a) std::cin >> e;
    for (auto &e : b) std::cin >> e;
    if (a[0] != b[0]) {
        std::cout << -1 << '\n';
        return 0;
    }
    std::vector<int> c(n - 1), d(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        c[i] = a[i] ^ a[i + 1];
        d[i] = b[i] ^ b[i + 1];
    }
    std::cout << swap_distance(c, d) << '\n';

    return 0;
}
