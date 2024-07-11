#include "template/template.hpp"

// i * j = g^(x + y) としてFFTに帰着
// verify : https://atcoder.jp/contests/agc047/tasks/agc047_c 21/02/24

namespace FFT {

void _fft(std::vector<std::complex<double>> &a, bool inv) {
    int N = a.size();
    static bool is_first = true;
    static std::array<std::complex<double>, 30> vbw, vibw;
    if (is_first) {
        is_first = false;
        for (int i = 0; i < 30; ++i) {
            vbw[i] = std::polar(1.0, 2.0 * PI / (1 << (i + 1)));
            vibw[i] = std::polar(1.0, -2.0 * PI / (1 << (i + 1)));
        }
    }
    for (int i = 0, j = 1; j < N - 1; ++j) {
        for (int k = N >> 1; k > (i ^= k); k >>= 1);
        if (i > j) std::swap(a[i], a[j]);
    }
    for (int k = 0, t = 1; t < N; ++k, t <<= 1) {
        std::complex<double> bw = vbw[k];
        if (inv) bw = vibw[k];
        for (int i = 0; i < N; i += t * 2) {
            std::complex<double> w(1.0);
            for (int j = 0; j < t; ++j) {
                int l = i + j, r = i + j + t;
                std::complex<double> c = a[l], d = a[r] * w;
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
void convolution_self(std::vector<T> &a, const std::vector<T> &b) {
    int n = a.size() + b.size() - 1;
    int N = 1;
    while (N < n) N <<= 1;

    std::vector<std::complex<double>> va(N), vb(N);
    for (int i = 0; i < (int)a.size(); ++i) va[i] = std::complex<double>(a[i]);
    for (int i = 0; i < (int)b.size(); ++i) vb[i] = std::complex<double>(b[i]);
    _fft(va, false), _fft(vb, false);
    for (int i = 0; i < N; ++i) va[i] *= vb[i];
    _fft(va, true);

    a.resize(n);
    if constexpr (std::numeric_limits<T>::is_integer)
        for (int i = 0; i < n; ++i) a[i] = T(va[i].real() + 0.5);
    else
        for (int i = 0; i < n; ++i) a[i] = va[i].real();
}

template <class T>
std::vector<T> convolution(const std::vector<T> &a, const std::vector<T> &b) {
    std::vector<T> res = a;
    convolution_self(res, b);
    return res;
}

}  // namespace FFT
