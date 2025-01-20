#pragma once
#include <vector>
#include "fft/formal_power_series.hpp"

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> bell(int n) {
    if (n == 0) return std::vector<mint>(1, mint(1));
    std::vector<mint> res(n + 1);
    res[1] = 1;
    res = fps::exp(res);
    res[0] -= 1;
    res = fps::exp(res);
    mint mul = 1;
    for (int i = 0; i <= n; ++i) {
        res[i] *= mul;
        mul *= i + 1;
    }
    return res;
}
