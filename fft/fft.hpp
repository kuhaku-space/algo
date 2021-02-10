#include "_base.hpp"

struct FFT {
    using CP = complex<double>;

    void _fft(vector<CP> &a, bool inv) {
        int64_t N = a.size();
        static bool is_first = true;
        static vector<CP> vbw(30), vibw(30);
        if (is_first) {
            is_first = false;
            for (int64_t i = 0; i < 30; ++i) {
                vbw[i] = polar(1.0, 2.0 * PI / (1 << (i + 1)));
                vibw[i] = polar(1.0, -2.0 * PI / (1 << (i + 1)));
            }
        }
        for (int64_t i = 0, j = 1; j < N - 1; ++j) {
            for (int64_t k = N >> 1; k > (i ^= k); k >>= 1)
                ;
            if (i > j) swap(a[i], a[j]);
        }
        for (int64_t k = 0, t = 1; t < N; ++k, t <<= 1) {
            CP bw = vbw[k];
            if (inv) bw = vibw[k];
            for (int64_t i = 0; i < N; i += t * 2) {
                CP w(1.0);
                for (int64_t j = 0; j < t; ++j) {
                    int64_t l = i + j, r = i + j + t;
                    CP c = a[l], d = a[r] * w;
                    a[l] = c + d;
                    a[r] = c - d;
                    w *= bw;
                }
            }
        }
        if (inv) {
            for (int64_t i = 0; i < N; ++i) a[i] /= N;
        }
    }

    vector<int64_t> convolution(const vector<int64_t> &a,
                                const vector<int64_t> &b) {
        int64_t n = a.size() + b.size() - 1;
        int64_t N = 1;
        while (N < n) N <<= 1;

        vector<CP> va(N), vb(N);
        for (int64_t i = 0; i < a.size(); ++i) va[i] = CP(a[i]);
        for (int64_t i = 0; i < b.size(); ++i) vb[i] = CP(b[i]);

        _fft(va, false);
        _fft(vb, false);

        for (int64_t i = 0; i < N; ++i) va[i] *= vb[i];

        _fft(va, true);

        vector<int64_t> ans(n);
        for (int64_t i = 0; i < n; ++i) {
            ans[i] = int64_t(va[i].real() + 0.5);
        }
    }

    void convolution_self(vector<int64_t> &a, const vector<int64_t> &b) {
        int64_t n = a.size() + b.size() - 1;
        int64_t N = 1;
        while (N < n) N <<= 1;

        vector<CP> va(N), vb(N);
        for (int64_t i = 0; i < a.size(); ++i) va[i] = CP(a[i]);

        for (int64_t i = 0; i < b.size(); ++i) vb[i] = CP(b[i]);

        _fft(va, false);
        _fft(vb, false);

        for (int64_t i = 0; i < N; ++i) va[i] *= vb[i];

        _fft(va, true);

        a.resize(n);
        for (int64_t i = 0; i < n; ++i) {
            a[i] = int64_t(va[i].real() + 0.5);
        }
    }
};

// i * j = g^(x + y) としてFFTに帰着
int64_t pow_mod(int64_t a, int64_t n, int64_t mod) {
    int64_t res = 1, mul = a;
    for (; n > 0; n >>= 1) {
        if (n & 1) (res *= mul) %= mod;
        (mul *= mul) %= mod;
    }
    return res;
}

int get_primitive_root(const int mod) {
    if (mod == 998244353) return 3;
    int64_t divs[20] = {};
    divs[0] = 2;
    int64_t cnt = 1;
    int64_t x = (mod - 1) / 2;
    while (x % 2 == 0) x /= 2;
    for (int64_t i = 3; i * i <= x; i += 2) {
        if (x % i == 0) {
            divs[cnt++] = i;
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) divs[cnt++] = x;
    for (int64_t g = 2;; ++g) {
        bool ok = true;
        for (int64_t i = 0; i < cnt; ++i) {
            if (pow_mod(g, (mod - 1) / divs[i], mod) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
    return 0;
}
