#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_1_C"
#include "math/eratosthenes.hpp"
#include "template/atcoder.hpp"

eratosthenes<100000001> pn;

int main(void) {
    int n;
    cin >> n;
    int ans = 0;
    while (n--) {
        int a;
        cin >> a;
        ans += pn.is_prime(a);
    }
    co(ans);

    return 0;
}
