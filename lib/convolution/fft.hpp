#pragma once
#include <array>
#include <bit>
#include <cassert>
#include <cmath>
#include <complex>
#include <concepts>
#include <cstdint>
#include <numbers>
#include <type_traits>
#include <vector>

namespace fft {

/// FFT で扱える最大長は 2^FFT_MAX_LOG。
static constexpr int FFT_MAX_LOG = 30;

/// @brief 複素 FFT (in-place, 反復 Cooley-Tukey)
/// @param a 長さが 2 冪の複素数列
/// @param inv true なら逆変換 (1/N でスケーリングする)
void _fft(std::vector<std::complex<double>> &a, bool inv) {
    int N = int(a.size());
    if (N <= 1) return;
    int log_n = std::countr_zero<unsigned>(N);
    assert((1 << log_n) == N && "FFT length must be a power of two.");
    assert(log_n <= FFT_MAX_LOG && "FFT length exceeds 2^FFT_MAX_LOG.");

    // 各段の回転因子 e^{±2πi / 2^(i+1)} を初回のみ事前計算する。
    static std::array<std::complex<double>, FFT_MAX_LOG> vbw, vibw;
    static bool is_first = true;
    if (is_first) {
        is_first = false;
        for (int i = 0; i < FFT_MAX_LOG; ++i) {
            vbw[i] = std::polar(1.0, 2.0 * std::numbers::pi / (1 << (i + 1)));
            vibw[i] = std::polar(1.0, -2.0 * std::numbers::pi / (1 << (i + 1)));
        }
    }

    // ビット反転並べ替え。
    for (int i = 0, j = 1; j < N - 1; ++j) {
        for (int k = N >> 1; k > (i ^= k); k >>= 1);
        if (i > j) std::swap(a[i], a[j]);
    }
    for (int k = 0, t = 1; t < N; ++k, t <<= 1) {
        std::complex<double> bw = inv ? vibw[k] : vbw[k];
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

/// @brief FFT による畳み込み
/// @tparam T 算術型 (整数型なら結果を最近接整数へ丸める)
/// @param a 入力多項式の係数列
/// @param b 入力多項式の係数列
/// @return std::vector<T> a と b の畳み込み (長さ a.size() + b.size() - 1)
template <class T>
requires std::is_arithmetic_v<T>
std::vector<T> convolution(const std::vector<T> &a, const std::vector<T> &b) {
    if (a.empty() || b.empty()) return {};
    int n = int(a.size() + b.size()) - 1;
    int N = std::bit_ceil<unsigned>(n);

    std::vector<std::complex<double>> va(N), vb(N);
    for (int i = 0; i < int(a.size()); ++i) va[i] = std::complex<double>(a[i]);
    for (int i = 0; i < int(b.size()); ++i) vb[i] = std::complex<double>(b[i]);
    _fft(va, false), _fft(vb, false);
    for (int i = 0; i < N; ++i) va[i] *= vb[i];
    _fft(va, true);

    std::vector<T> res(n);
    if constexpr (std::is_integral_v<T>)
        for (int i = 0; i < n; ++i) res[i] = T(std::llround(va[i].real()));
    else
        for (int i = 0; i < n; ++i) res[i] = T(va[i].real());
    return res;
}

/// @brief 任意 mod 畳み込み (実数 FFT を 15bit 分割で 3 回適用)
/// @details 係数を上位 15bit / 下位 15bit に分けて a = a1*2^15 + a0 とし、
///          a1*b1, a0*b0, (a1+a0)(b1+b0) の 3 回の畳み込みから復元する。
///          double の精度の範囲 (mod^2 * 長さ が約 2^53 以下) で正しい。
/// @tparam T 整数型
/// @param a 入力多項式の係数列 ([0, mod) を想定)
/// @param b 入力多項式の係数列 ([0, mod) を想定)
/// @param mod 出力を取る法 (NTT-friendly でなくてよい)
/// @return std::vector<T> a と b の畳み込みを mod で取った値 (長さ a.size() + b.size() - 1)
template <std::integral T>
std::vector<T> convolution_mod(const std::vector<T> &a, const std::vector<T> &b, T mod) {
    if (a.empty() || b.empty()) return {};
    int n = int(a.size()), m = int(b.size());
    int N = std::bit_ceil<unsigned>(n + m - 1);

    // 各係数を上位 a1 = (a >> 15) と下位 a0 = (a & (2^15 - 1)) に分割し、複素 FFT にかける。
    std::vector<std::complex<double>> a1(N), a0(N), b1(N), b0(N);
    for (int i = 0; i < n; ++i) {
        a1[i] = std::complex<double>(double(a[i] >> 15));
        a0[i] = std::complex<double>(double(a[i] & ((1 << 15) - 1)));
    }
    for (int i = 0; i < m; ++i) {
        b1[i] = std::complex<double>(double(b[i] >> 15));
        b0[i] = std::complex<double>(double(b[i] & ((1 << 15) - 1)));
    }
    _fft(a1, false), _fft(a0, false), _fft(b1, false), _fft(b0, false);

    // x = a1*b1, z = a0*b0, y = (a1+a0)(b1+b0) - x - z = a1*b0 + a0*b1。
    std::vector<std::complex<double>> x(N), y(N), z(N);
    for (int i = 0; i < N; ++i) {
        x[i] = a1[i] * b1[i];
        z[i] = a0[i] * b0[i];
        y[i] = (a1[i] + a0[i]) * (b1[i] + b0[i]) - x[i] - z[i];
    }
    _fft(x, true), _fft(y, true), _fft(z, true);

    // 結果 = x*2^30 + y*2^15 + z (各段で mod を取り、オーバーフローを避ける)。
    static constexpr std::uint64_t MASK15 = 1 << 15;
    const std::uint64_t umod = std::uint64_t(mod);
    std::vector<T> res(n + m - 1);
    for (int i = 0; i < n + m - 1; ++i) {
        std::uint64_t xi = std::uint64_t(std::llround(x[i].real())) % umod;
        std::uint64_t yi = std::uint64_t(std::llround(y[i].real())) % umod;
        std::uint64_t zi = std::uint64_t(std::llround(z[i].real())) % umod;
        // ((xi * 2^15 + yi) * 2^15 + zi) mod。各乗算は < mod * 2^15 < 2^64。
        std::uint64_t r = (((xi * MASK15 + yi) % umod) * MASK15 + zi) % umod;
        res[i] = T(r);
    }
    return res;
}

}  // namespace fft
