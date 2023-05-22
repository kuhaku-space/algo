#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_1_C"
#include "math/prime_number.hpp"
#include "template/atcoder.hpp"

prime_number pn;

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
