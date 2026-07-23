#pragma once
#include <algorithm>
#include <concepts>
#include <vector>

/// @brief XOR (F2 上の線形) 基底
template <std::unsigned_integral T>
struct XorBasis {
    XorBasis() = default;

    /// @brief x を基底へ追加する。基底を拡張できたら true
    bool insert(T x) {
        x = reduce(x);
        if (x == T()) return false;
        for (T &b : basis) b = std::min(b, b ^ x);
        basis.emplace_back(x);
        std::sort(basis.rbegin(), basis.rend());
        return true;
    }

    /// @brief x を基底で簡約する。0 になれば x は基底の張る空間に含まれる
    T reduce(T x) const {
        for (T b : basis) x = std::min(x, x ^ b);
        return x;
    }

    /// @brief x が基底の張る空間に含まれるかどうか
    bool contains(T x) const { return reduce(x) == T(); }

    /// @brief x との xor を最大化する値を返す
    T max_xor(T x = T()) const {
        for (T b : basis) x = std::max(x, x ^ b);
        return x;
    }

    int size() const { return basis.size(); }
    bool empty() const { return basis.empty(); }

  private:
    std::vector<T> basis;
};
