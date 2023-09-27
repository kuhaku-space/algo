#define PROBLEM "https://yukicoder.me/problems/no/1977"
#include "algorithm/doubling.hpp"
#include "template/atcoder.hpp"

struct Monoid {
    using value_type = ll;
    static constexpr ll id = 0;
    static constexpr ll op(const ll &lhs, const ll &rhs) { return lhs + rhs; }
};

int main(void) {
    ll n, m, l;
    std::cin >> n >> m >> l;
    std::vector<int> a(n);
    std::cin >> a;
    std::vector<int> to(n);
    rep (i, n) to[i] = (i + l) % n;
    Doubling<40, Monoid> db(to, a);
    ll r = (n * m) % l;
    ll k = (n * m) / l;
    ll ans = -INF;
    rep (i, min(r, n)) chmax(ans, db.solve(i, k + 1).second);
    rep (i, min(l - r, n)) chmax(ans, db.solve((r + i) % n, k).second);
    co(ans);

    return 0;
}
