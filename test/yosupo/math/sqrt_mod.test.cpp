#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"
#include "math/modint.hpp"
#include "math/sqrt.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int t;
    cin >> t;
    while (t--) {
        int y, p;
        cin >> y >> p;
        modint::set_mod(p);
        modint x(y);
        if (!has_sqrt_mod(x)) co(-1);
        else co(sqrt_mod(x));
    }

    return 0;
}
