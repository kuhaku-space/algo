#include "template/template.hpp"

// i * j = g^(x + y) としてFFTに帰着
// verify : https://atcoder.jp/contests/agc047/tasks/agc047_c 21/02/24

namespace FFT {
using CP = complex<double>;

void _fft(vector<CP> &a, bool inv) {
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
        for (int i = 0; i < N; ++i) a[i] /= N;
    }
}

template <class T>
void convolution_self(vector<T> &a, const vector<T> &b) {
    int n = a.size() + b.size() - 1;
    int N = 1;
    while (N < n) N <<= 1;

    vector<CP> va(N), vb(N);
    for (int i = 0; i < a.size(); ++i) va[i] = CP(a[i]);
    for (int i = 0; i < b.size(); ++i) vb[i] = CP(b[i]);
    _fft(va, false), _fft(vb, false);
    for (int i = 0; i < N; ++i) va[i] *= vb[i];
    _fft(va, true);

    a.resize(n);
    for (int i = 0; i < n; ++i) a[i] = T(va[i].real() + 0.5);
}

template <class T>
vector<T> convolution(const vector<T> &a, const vector<T> &b) {
    vector<T> res = a;
    convolution_self(res, b);
    return res;
}
}  // namespace FFT
