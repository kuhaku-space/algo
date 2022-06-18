#pragma once
#include "math/modint.hpp"
#include "math/pow.hpp"
#include "template/template.hpp"

/**
 * @brief 数論変換
 * @see https://hcpc-hokudai.github.io/archive/math_fft_002.pdf
 *
 * @tparam mod 法
 * @tparam primitive_root 原始根
 */
template <int mod = MOD_N, int primitive_root = 3>
struct NTT {
    using mint = ModInt<mod>;
    static constexpr int get_mod() { return mod; }

    template <class T, class U>
    static void convolution_self(std::vector<T> &a, std::vector<U> b) {
        int n = a.size() + b.size() - 1;
        int N = 1 << ceil_pow2(n);
        a.resize(N), b.resize(N);

        _ntt(a, false), _ntt(b, false);

        for (int i = 0; i < N; ++i) a[i] = T(1LL * a[i] * b[i] % mod);

        _ntt(a, true);
        a.resize(n);
    }

    template <class T, class U>
    static std::vector<T> convolution(const std::vector<T> &a, const std::vector<U> &b) {
        std::vector<T> res = a;
        convolution_self(res, b);
        return res;
    }

  private:
    template <class T>
    static void _ntt(std::vector<T> &a, bool inv) {
        int N = a.size();
        static bool is_first = true;
        static std::array<mint, 30> vbw, vibw;
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
                    a[l] = int(c + d);
                    a[r] = int(c - d);
                    w *= bw;
                }
            }
        }
        if (inv) {
            int m = int(mint(N).inverse());
            for (int i = 0; i < N; ++i) a[i] = T(1LL * a[i] * m % mod);
        }
    }
};
