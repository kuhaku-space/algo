#include "math/modint.hpp"

template <class mint, internal::is_modint_t<mint> * = nullptr>
bool has_sqrt_mod(mint x) {
    return x == 0 || x.pow(mint::mod() / 2) == 1;
}

template <class mint, internal::is_modint_t<mint> * = nullptr>
mint sqrt_mod(mint x) {
    const int p = mint::mod();
    if (x == 0 || x == 1) return x;
    if (p % 4 == 3) return x.pow(p / 4 + 1);
    int q = p - 1, s = 0;
    while (~q & 1) q >>= 1, ++s;
    mint z(1);
    while (has_sqrt_mod(z)) ++z;
    mint c = z.pow(q);
    mint t = x.pow(q);
    mint r = x.pow(q / 2 + 1);
    while (t != 1) {
        int m = 0;
        mint u = t;
        while (u != 1) ++m, u *= u;
        while (s != m) {
            --s;
            if (s == m) r *= c;
            c *= c;
        }
        t *= c;
    }
    return r;
}
