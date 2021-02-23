#include <random>

#include "_base.hpp"

// verify : https://atcoder.jp/contests/abc141/tasks/abc141_e 21/02/24

struct rolling_hash {
    const uint64_t mod = (1ul << 61) - 1;
    const uint64_t mask30 = (1ul << 30) - 1;
    const uint64_t mask31 = (1ul << 31) - 1;
    uint64_t base, len;
    vector<uint64_t> data, p;

    rolling_hash(const string &_s) : data(1), p(1, 1), len(_s.size() + 1) {
        random_device seed;
        mt19937 mt(seed());
        base = mt() + 2;
        uint64_t x = 0, t = 1;
        for (const auto c : _s) {
            x = _mod(_mul(x, base) + c);
            data.emplace_back(x);
            t = _mod(_mul(t, base));
            p.emplace_back(t);
        }
    }

    uint64_t _mul(uint64_t a, uint64_t b) {
        uint64_t au = a >> 31, ad = a & mask31;
        uint64_t bu = b >> 31, bd = b & mask31;
        uint64_t mid = ad * bu + au * bd;
        uint64_t midu = mid >> 30, midd = mid & mask30;
        return au * bu * 2 + midu + (midd << 31) + ad * bd;
    }

    uint64_t _mod(uint64_t x) {
        uint64_t xu = x >> 61, xd = x & mod;
        uint64_t res = xu + xd;
        if (res >= mod) res -= mod;
        return res;
    }

    uint64_t _pow(uint64_t x, uint64_t k) {
        uint64_t res = 1;
        for (; k; k >>= 1) {
            if (k & 1) res = _mod(_mul(res, x));
            x = _mod(_mul(x, x));
        }
        return res;
    }

    inline uint64_t get(int l, int r) {
        return _mod(data[r] + mod * 4 - _mul(data[l], p[r - l]));
    }

    vector<int> search(const string &s) {
        vector<int> res;
        int n = s.size();
        if (n >= len) return res;
        uint64_t x = 0;
        for (const auto c : s) x = _mod(_mul(x, base) + c);
        for (int i = n; i < len; ++i) {
            if (get(i - n, i) == x) res.emplace_back(i - n);
            x = _mod(_mul(x, base));
        }
        return res;
    }
};
