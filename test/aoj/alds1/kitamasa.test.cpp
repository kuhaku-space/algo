#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_10_A"
#include "math/kitamasa.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n;
    std::cin >> n;
    std::vector<ll> a(2, 1), d(2, 1);
    co(kitamasa(a, d, n));

    return 0;
}
