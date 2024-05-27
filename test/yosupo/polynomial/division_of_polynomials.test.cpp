#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"
#include <iostream>
#include <vector>

#include "fft/formal_power_series.hpp"

using Mint = modint998;

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::vector<Mint> f(n), g(m);
    for (Mint &e : f) std::cin >> e;
    for (Mint &e : g) std::cin >> e;
    auto [q, r] = fps::div_mod(f, g);
    std::cout << q.size() << ' ' << r.size() << '\n';
    if (q.empty()) {
        std::cout << '\n';
    } else {
        for (int i = 0; i < (int)q.size(); ++i) {
            std::cout << q[i] << (i == (int)q.size() - 1 ? '\n' : ' ');
        }
    }
    if (r.empty()) {
        std::cout << '\n';
    } else {
        for (int i = 0; i < (int)r.size(); ++i) {
            std::cout << r[i] << (i == (int)r.size() - 1 ? '\n' : ' ');
        }
    }

    return 0;
}
