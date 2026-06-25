// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/discrete_logarithm_mod
#include <iostream>
#include "math/modint.hpp"
#include "number_theory/discrete_log.hpp"
#include "segtree/monoid.hpp"

int main(void) {
    using mint = modint;
    int t;
    std::cin >> t;
    while (t--) {
        int x, y, m;
        std::cin >> x >> y >> m;
        mint::set_mod(m);
        // X^n ≡ Y (mod m) を満たす最小の n を [0, m) から求める
        std::int64_t ans = discrete_log_monoid<Mul<mint>>(mint(x), mint(y), [](mint v) { return v.val(); }, 0, m);
        std::cout << ans << '\n';
    }

    return 0;
}
