// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/inv_of_polynomials
#include <iostream>
#include <vector>
#include "convolution/formal_power_series.hpp"

using Mint = modint998;

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::vector<Mint> f(n), g(m);
    for (auto &e : f) std::cin >> e;
    for (auto &e : g) std::cin >> e;
    auto h = fps::inv_of_polynomials(f, g);
    if (!h) {
        std::cout << -1 << '\n';
        return 0;
    }
    // h は末尾 0 を除いた正規形 (零多項式なら空)。係数数を出力し係数列を続ける。
    std::cout << h->size() << '\n';
    for (int i = 0; i < (int)h->size(); ++i) std::cout << (*h)[i] << " \n"[i + 1 == (int)h->size()];
    return 0;
}
