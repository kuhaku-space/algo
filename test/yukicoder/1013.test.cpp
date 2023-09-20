#define PROBLEM "https://yukicoder.me/problems/no/1013"
#include "algorithm/doubling.hpp"
#include "template/atcoder.hpp"

struct Monoid {
    using value_type = ll;
    static constexpr ll id = 0;
    static constexpr ll op(const ll &lhs, const ll &rhs) { return lhs + rhs; }
};

int main(void) {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> p(n);
    std::cin >> p;
    std::vector<int> to(n);
    rep (i, n) to[i] = (i + p[i]) % n;
    Doubling<30, Monoid> db(to, p);
    rep (i, n) co(i + 1 + db.solve(i, k).second);

    return 0;
}
