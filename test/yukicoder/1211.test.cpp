#define PROBLEM "https://yukicoder.me/problems/no/1211"
#include "graph/functional_graph.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, k;
    std::cin >> n >> k;
    std::vector<ll> a(n);
    std::cin >> a;
    auto b = a;
    b.insert(b.begin(), 0);
    b.insert(b.end(), all(a));
    rep (i, n * 2) b[i + 1] += b[i];
    ll l = 1, r = b[n] / k + 1;
    std::vector<int> to(n * 2 + 2, n * 2 + 1);
    while (r - l > 1) {
        ll m = (l + r) / 2;
        int idx = 0;
        rep (i, n * 2) {
            while (idx < (int)b.size() && b[idx] - b[i] < m) ++idx;
            to[i] = idx;
        }
        functional_graph fg(to);
        auto v = fg.jump_all(k);
        bool f = false;
        rep (i, n) {
            if (v[i] - i <= n) {
                f = true;
                break;
            }
        }
        (f ? l : r) = m;
    }
    co(l);

    return 0;
}
