#define PROBLEM "https://yukicoder.me/problems/no/1097"
#include "algorithm/doubling.hpp"
#include "template/atcoder.hpp"

struct Monoid {
    using value_type = ll;
    static constexpr ll id = 0;
    static constexpr ll op(const ll &lhs, const ll &rhs) { return lhs + rhs; }
};

int main(void) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::cin >> a;
    std::vector<int> to(n);
    rep (i, n) to[i] = (i + a[i]) % n;
    Doubling<40, Monoid> db(to, a);
    int q;
    std::cin >> q;
    while (q--) {
        ll k;
        std::cin >> k;
        co(db.solve(0, k).second);
    }

    return 0;
}
