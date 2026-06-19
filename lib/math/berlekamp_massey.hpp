#pragma once
#include <utility>
#include <vector>

/// @brief Berlekamp-Massey 法
/// 数列 s と矛盾しない最小位数の線形漸化式の係数 c を求める
/// s_i = \sum_{j=1}^{L} c_{j-1} s_{i-j} (i >= L) を満たす
template <class T>
std::vector<T> berlekamp_massey(const std::vector<T> &s) {
    const int n = s.size();
    // c: 現在の漸化式の係数 (c[0] = 1)、b: 前回更新時の係数
    std::vector<T> c{T(1)}, b{T(1)};
    // m: 前回 c を更新してからの経過、d_b: 前回の差分
    int len = 0, m = 1;
    T d_b = T(1);
    for (int i = 0; i < n; ++i) {
        // 差分 d = \sum_{j=0}^{len} c[j] s_{i-j} を計算
        T d = s[i];
        for (int j = 1; j <= len; ++j) d += c[j] * s[i - j];
        if (d == T(0)) {
            ++m;
            continue;
        }
        const T coef = d / d_b;
        if (2 * len <= i) {
            // 位数が増える更新。c を退避してから b と合成する
            std::vector<T> tmp = c;
            c.resize(std::max<int>(c.size(), b.size() + m), T(0));
            for (int j = 0; j < (int)b.size(); ++j) c[j + m] -= coef * b[j];
            len = i + 1 - len;
            b = std::move(tmp);
            d_b = d;
            m = 1;
        } else {
            // 位数は変えず c のみ修正する
            c.resize(std::max<int>(c.size(), b.size() + m), T(0));
            for (int j = 0; j < (int)b.size(); ++j) c[j + m] -= coef * b[j];
            ++m;
        }
    }
    // c = [1, -c_1, ..., -c_L] の形なので漸化式係数 [c_1, ..., c_L] に変換する
    std::vector<T> res(len);
    for (int i = 0; i < len; ++i) res[i] = -c[i + 1];
    return res;
}
