#pragma once
#include <cmath>
#include <cstdint>
#include <numeric>

/// @brief めぐる式二分探索
template <class T, class F>
std::int64_t meguru_binary_search(T ok, T ng, F check) {
    while (std::abs(ok - ng) > 1) {
        T mid = std::midpoint(ok, ng);
        (check(mid) ? ok : ng) = mid;
    }
    return ok;
}
