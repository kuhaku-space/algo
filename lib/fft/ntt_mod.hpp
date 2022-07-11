#pragma once
#include "fft/garner.hpp"
#include "fft/ntt.hpp"
#include "template/template.hpp"

using NTT_1 = NTT<167772161, 3>;   // 2^25 * 5 + 1
using NTT_2 = NTT<469762049, 3>;   // 2^26 * 7 + 1
using NTT_3 = NTT<998244353, 3>;   // 2^23 * 119 + 1
using NTT_4 = NTT<1224736769, 3>;  // 2^24 * 73 + 1

/**
 * @brief 任意mod数論変換
 * @see https://math314.hateblo.jp/entry/2015/05/07/014908
 * @see https://asako.growi.cloud/compro/NTT
 *
 * @tparam T
 * @param a
 * @param b
 * @param mod
 * @return std::vector<int>
 */
template <class T, class U>
std::vector<int> convolution(std::vector<T> a, std::vector<U> b, int mod) {
    const int n = a.size() + b.size() - 1;
    for (auto& i : a) i %= mod;
    for (auto& i : b) i %= mod;
    auto x = NTT_1::convolution(a, b);
    auto y = NTT_2::convolution(a, b);
    auto z = NTT_3::convolution(a, b);

    std::vector<int> res(n);
    std::vector<int> r(3), m(3);
    for (int i = 0; i < n; ++i) {
        r[0] = (int)x[i], m[0] = NTT_1::get_mod();
        r[1] = (int)y[i], m[1] = NTT_2::get_mod();
        r[2] = (int)z[i], m[2] = NTT_3::get_mod();
        res[i] = garner(r, m, mod);
    }

    return res;
}

template <class T>
std::vector<T> power(std::vector<T> v, std::int64_t x, int mod = MOD) {
    int n = v.size();
    std::vector<T> res(n);
    res[0] = 1;
    for (; x; x >>= 1) {
        if (x & 1) {
            res = convolution(res, v, mod);
            res.resize(n);
        }
        v = convolution(v, v, mod);
        v.resize(n);
    }
    return res;
}
