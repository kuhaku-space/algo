#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_A"
#include "math/prime_number.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n;
    cin >> n;
    auto v = pn.prime_factorization(n);
    cout << n << ':';
    for (auto p : v) {
        rep(i, p.second) cout << ' ' << p.first;
    }
    cout << '\n';

    return 0;
}
