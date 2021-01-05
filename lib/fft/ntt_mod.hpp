#include "_base.hpp"
#include "fft/garner.hpp"
#include "fft/ntt.hpp"
#include "modint.hpp"

using NTT_1 = NTT<167772161, 3>;   // 2^25 * 5 + 1
using NTT_2 = NTT<469762049, 3>;   // 2^26 * 7 + 1
using NTT_3 = NTT<1224736769, 3>;  // 2^24 * 73 + 1

vector<int64_t> convolution(vector<int64_t> a, vector<int64_t> b, int mod) {
    const int64_t n = a.size() + b.size() - 1;
    for (auto& i : a) i %= mod;
    for (auto& i : b) i %= mod;
    NTT_1 ntt1;
    NTT_2 ntt2;
    NTT_3 ntt3;
    auto x = ntt1.convolution(a, b);
    auto y = ntt2.convolution(a, b);
    auto z = ntt3.convolution(a, b);

    vector<int64_t> res(n);
    vector<int64_t> r(3), m(3);
    for (int64_t i = 0; i < n; ++i) {
        r[0] = x[i], m[0] = ntt1.get_mod();
        r[1] = y[i], m[1] = ntt2.get_mod();
        r[2] = z[i], m[2] = ntt3.get_mod();
        res[i] = garner(r, m, mod);
    }

    return res;
}

vector<int64_t> power(vector<int64_t> v, int64_t x) {
    int64_t n = v.size();
    vector<int64_t> res(n);
    res[0] = 1;
    for (; x > 0; x >>= 1) {
        if (x & 1) {
            res = convolution(res, v, MOD);
            res.resize(n);
        }
        v = convolution(v, v, MOD);
        v.resize(n);
    }
    return res;
}
