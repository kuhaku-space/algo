// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/551
#include <cstdint>
#include <iostream>
#include "math/modint.hpp"
#include "number_theory/root_mod.hpp"

using Mint = modint;

int main(void) {
    int p, r;
    std::cin >> p >> r;
    Mint::set_mod(p);
    int q;
    std::cin >> q;
    while (q--) {
        std::int64_t a, b, c;
        std::cin >> a >> b >> c;
        std::int64_t d = b * b - 4 * a * c;
        Mint x = Mint(-b) / 2 / a;
        if (auto d_sqrt = sqrt_mod<Mint>(d)) {
            Mint y = *d_sqrt / 2 / a;
            if (x - y == x + y) std::cout << x + y << '\n';
            else if ((x - y).val() < (x + y).val()) std::cout << x - y << ' ' << x + y << '\n';
            else std::cout << x + y << ' ' << x - y << '\n';
        } else {
            std::cout << -1 << '\n';
        }
    }

    return 0;
}
