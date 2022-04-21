#include "math/pow.hpp"
#include "template/template.hpp"

int get_primitive_root(const int mod) {
    if (mod == 998244353) return 3;
    int64_t divs[20] = {};
    divs[0] = 2;
    int64_t cnt = 1;
    int64_t x = (mod - 1) / 2;
    while (x % 2 == 0) x /= 2;
    for (int64_t i = 3; i * i <= x; i += 2) {
        if (x % i == 0) {
            divs[cnt++] = i;
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) divs[cnt++] = x;
    for (int64_t g = 2;; ++g) {
        bool ok = true;
        for (int64_t i = 0; i < cnt; ++i) {
            if (pow_mod(g, (mod - 1) / divs[i], mod) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
    return 0;
}
