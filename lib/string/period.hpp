#pragma once
#include "string/z_algorithm.hpp"

/// @brief s を隙間なく敷き詰める最小の周期を求める (s の長さを割り切る最小の i)
/// @complexity O(N)
template <class Container>
int minimum_period(const Container &s) {
    auto z = z_algorithm(s);
    int n = s.size();
    for (int i = 1; i <= n / 2; ++i) {
        if (n % i == 0 && z[i] == n - i) return i;
    }
    return n;
}
