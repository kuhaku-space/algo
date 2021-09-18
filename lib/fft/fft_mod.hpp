#include "template/template.hpp"

namespace FFT_MOD {
using CP = complex<double>;

void _fft(valarray<CP> &a, bool inv) {
    int N = a.size();
    static bool is_first = true;
    static vector<CP> vbw(30), vibw(30);
    if (is_first) {
        is_first = false;
        for (int i = 0; i < 30; ++i) {
            vbw[i] = polar(1.0, 2.0 * PI / (1 << (i + 1)));
            vibw[i] = polar(1.0, -2.0 * PI / (1 << (i + 1)));
        }
    }
    for (int i = 0, j = 1; j < N - 1; ++j) {
        for (int k = N >> 1; k > (i ^= k); k >>= 1)
            ;
        if (i > j) swap(a[i], a[j]);
    }
    for (int k = 0, t = 1; t < N; ++k, t <<= 1) {
        CP bw = vbw[k];
        if (inv) bw = vibw[k];
        for (int i = 0; i < N; i += t * 2) {
            CP w(1.0);
            for (int j = 0; j < t; ++j) {
                int l = i + j, r = i + j + t;
                CP c = a[l], d = a[r] * w;
                a[l] = c + d, a[r] = c - d;
                w *= bw;
            }
        }
    }
    if (inv) {
        a /= N;
    }
}

template <class T>
void _convolution_self(valarray<T> &a, const valarray<T> &b) {
    int n = a.size() + b.size() - 1;
    int N = 1;
    while (N < n) N <<= 1;

    valarray<CP> va(N), vb(N);
    for (int i = 0; i < a.size(); ++i) va[i] = CP(a[i]);
    for (int i = 0; i < b.size(); ++i) vb[i] = CP(b[i]);
    _fft(va, false), _fft(vb, false);
    va *= vb;
    _fft(va, true);

    a.resize(n);
    for (int i = 0; i < n; ++i) a[i] = T(va[i].real() + 0.5);
}

template <class T>
valarray<T> _convolution(const valarray<T> &a, const valarray<T> &b) {
    valarray<T> res = a;
    _convolution_self(res, b);
    return res;
}

template <class T>
vector<T> convolution(const vector<T> &a, const vector<T> &b, int mod) {
    int n = a.size(), m = b.size();
    valarray<T> v(n), w(m);
    for (int i = 0; i < n; ++i) v[i] = a[i];
    for (int i = 0; i < m; ++i) w[i] = b[i];
    auto f1 = v, f2 = v;
    auto g1 = w, g2 = w;
    f1 >>= 15;
    f2 &= (1 << 15) - 1;
    g1 >>= 15;
    g2 &= (1 << 15) - 1;

    auto x = _convolution(f1, g1);
    x %= mod;
    auto z = _convolution(f2, g2);
    z %= mod;
    f1 += f2;
    g1 += g2;
    auto y = _convolution(f1, g1);
    y -= x;
    y -= z;
    y %= mod;
    x <<= 15;
    x += y;
    x <<= 15;
    x += z;
    x %= mod;
    vector<T> res(n + m - 1);
    for (int i = 0; i < n + m - 1; ++i) res[i] = x[i];
    return res;
}
}  // namespace FFT_MOD
