#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int t;
    cin >> t;
    rep(i, t) {
        ll a, b;
        cin >> a >> b;
        co(a + b);
    }
    
    return 0;
}
