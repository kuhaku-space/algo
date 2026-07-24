#pragma once
#include <cmath>
#include <cstdint>
#include <numeric>

/// @brief めぐる式二分探索
/// @param ok 条件を満たすことが既知の初期値
/// @param ng 条件を満たさないことが既知の初期値
/// @param check 単調な判定関数
/// @return 条件を満たす境界側の値
/// @complexity 初期間隔を $D=|ok-ng|$ として $O(\log D)$ 回の判定
template <class T, class F>
T meguru_binary_search(T ok, T ng, F check) {
    while (std::abs(ok - ng) > 1) {
        T mid = std::midpoint(ok, ng);
        (check(mid) ? ok : ng) = mid;
    }
    return ok;
}
