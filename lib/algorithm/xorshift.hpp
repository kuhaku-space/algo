#pragma once
#include "template/template.hpp"

/**
 * @brief 擬似乱数生成器
 * 
 */
struct Xorshift {
    unsigned int x, y, z, w;

    Xorshift() { x = 123456789, y = 362436069, z = 521288629, w = 88675123; }

    using result_type = unsigned int;
    constexpr unsigned int min() { return 0; }
    constexpr unsigned int max() { return UINT32_MAX; }
    unsigned int operator()() {
        unsigned int t = (x ^ (x << 11));
        x = y, y = z, z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

    double rand_d() { return (double)(*this)() / (1LL << 32); }
};
