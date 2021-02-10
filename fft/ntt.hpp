#include "_base.hpp"
#include "algo/modint.hpp"

template <int mod, int primitive_root>
struct NTT {
    using mint = ModInt<mod>;
    const int get_mod() const { return mod; }
    void _ntt(vector<int64_t> &a, bool inv) {
        int64_t N = a.size();
        int64_t pr = primitive_root;
        static bool is_first = true;
        static vector<mint> vbw(30), vibw(30);
        if (is_first) {
            is_first = false;
            for (int64_t i = 0; i < 30; ++i) {
                vbw[i] = mint(pr).pow((mod - 1) >> (i + 1));
                vibw[i] = vbw[i].inverse();
            }
        }
        for (int64_t i = 0, j = 1; j < N - 1; ++j) {
            for (int64_t k = N >> 1; k > (i ^= k); k >>= 1)
                ;
            if (i > j) swap(a[i], a[j]);
        }
        for (int64_t k = 0, t = 1; t < N; ++k, t <<= 1) {
            mint bw = vbw[k];
            if (inv) bw = vibw[k];
            for (int64_t i = 0; i < N; i += t * 2) {
                mint w = 1;
                for (int64_t j = 0; j < t; ++j) {
                    int64_t l = i + j, r = i + j + t;
                    mint c = a[l], d = w * a[r];
                    a[l] = (c + d).to_int();
                    a[r] = (c - d).to_int();
                    w *= bw;
                }
            }
        }
        if (inv) {
            mint m = mint(N).inverse();
            for (int64_t i = 0; i < N; ++i) a[i] = (m * a[i]).to_int();
        }
    }

    vector<int64_t> convolution(vector<int64_t> a, vector<int64_t> b) {
        int64_t n = a.size() + b.size() - 1;
        int64_t N = 1;
        while (N < n) N <<= 1;
        a.resize(N);
        b.resize(N);

        _ntt(a, false);
        _ntt(b, false);

        vector<ll> res(N);
        for (int64_t i = 0; i < N; ++i) {
            res[i] = a[i] * b[i] % mod;
        }

        _ntt(res, true);
        res.resize(n);
        return res;
    }

    void convolution_self(vector<int64_t> &a, vector<int64_t> b) {
        int64_t n = a.size() + b.size() - 1;
        int64_t N = 1;
        while (N < n) N <<= 1;
        a.resize(N);
        b.resize(N);

        _ntt(a, false);
        _ntt(b, false);

        vector<ll> res(N);
        for (int64_t i = 0; i < N; ++i) {
            (a[i] *= b[i]) %= mod;
        }

        _ntt(a, true);
        a.resize(n);
    }
};

using Ntt = NTT<MOD_N, 3>;