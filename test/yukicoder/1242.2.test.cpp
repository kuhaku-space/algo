#define PROBLEM "https://yukicoder.me/problems/no/1242"
#include "algorithm/doubling.hpp"
#include "template/atcoder.hpp"

int main(void) {
    ll n;
    int k;
    std::cin >> n >> k;
    std::vector<ll> a(k);
    std::cin >> a;
    std::reverse(a.begin(), a.end());
    std::vector<int> to(1 << 6);
    rep (bit, 1 << 6) {
        int f = 0;
        rep (i, 3) f |= (bit >> i & 1) && (bit >> (5 - i) & 1);
        to[bit] = ((bit << 1) | f) & ((1 << 6) - 1);
    }
    Doubling<60> db(to);
    int cur = 1;
    rep (i, k - 1) {
        cur = db.solve(cur, a[i] - a[i + 1]);
        cur |= 1;
    }
    No(db.solve(cur, a.back() - 1) & 1);

    return 0;
}
