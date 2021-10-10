#include "math/modint.hpp"
#include "template/template.hpp"

template <int mod, int primitive_root>
struct NTT {
    using mint = ModInt<mod>;
    const int get_mod() const { return mod; }
    template <class T>
    void _ntt(vector<T> &a, bool inv) {
        int N = a.size();
        static bool is_first = true;
        static array<mint, 30> vbw, vibw;
        if (is_first) {
            is_first = false;
            for (int i = 0; i < 30; ++i) {
                vbw[i] = mint(primitive_root).pow((mod - 1) >> (i + 1));
                vibw[i] = vbw[i].inverse();
            }
        }
        for (int i = 0, j = 1; j < N - 1; ++j) {
            for (int k = N >> 1; k > (i ^= k); k >>= 1)
                ;
            if (i > j) swap(a[i], a[j]);
        }
        for (int k = 0, t = 1; t < N; ++k, t <<= 1) {
            mint bw = vbw[k];
            if (inv) bw = vibw[k];
            for (int i = 0; i < N; i += t * 2) {
                mint w = 1;
                for (int j = 0; j < t; ++j) {
                    int l = i + j, r = i + j + t;
                    mint c = a[l], d = w * a[r];
                    a[l] = (c + d).to_int();
                    a[r] = (c - d).to_int();
                    w *= bw;
                }
            }
        }
        if (inv) {
            int m = mint(N).inverse().to_int();
            for (int i = 0; i < N; ++i) a[i] = T(1LL * a[i] * m % mod);
        }
    }

    template <class T>
    void convolution_self(vector<T> &a, vector<T> b) {
        int n = a.size() + b.size() - 1;
        int N = 1;
        while (N < n) N <<= 1;
        a.resize(N), b.resize(N);

        _ntt(a, false), _ntt(b, false);

        for (int i = 0; i < N; ++i) a[i] = T(1LL * a[i] * b[i] % mod);

        _ntt(a, true);
        a.resize(n);
    }

    template <class T>
    vector<T> convolution(const vector<T> &a, const vector<T> &b) {
        vector<T> res = a;
        convolution_self(res, b);
        return res;
    }
};

using NTT_N = NTT<MOD_N, 3>;
