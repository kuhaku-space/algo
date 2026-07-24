#pragma once
#include <array>
#include <cstdint>
#include <limits>
#include <utility>

/// @brief 擬似乱数生成器 Xorshift
/// @complexity すべての操作が $O(1)$
struct Xorshift {
    /// @brief 内部状態の型
    /// @complexity 型エイリアスで実行時計算量はない
    using state_type = std::array<std::uint32_t, 4>;

    /// @brief 生成結果の型
    /// @complexity 型エイリアスで実行時計算量はない
    using result_type = std::uint32_t;

    /// @brief 既定seedで構築する
    /// @complexity $O(1)$
    constexpr Xorshift() : state{123456789, 362436069, 521288629, 88675123} {}

    /// @brief 生成しうる最小値を返す
    /// @complexity $O(1)$
    static constexpr result_type min() { return std::numeric_limits<result_type>::min(); }

    /// @brief 生成しうる最大値を返す
    /// @complexity $O(1)$
    static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }

    /// @brief 次の32bit乱数を返す
    /// @complexity $O(1)$
    result_type operator()() {
        std::uint32_t t = (state[0] ^ (state[0] << 11));
        state[0] = state[1], state[1] = state[2], state[2] = state[3];
        return state[3] = (state[3] ^ (state[3] >> 19)) ^ (t ^ (t >> 8));
    }

    /// @brief 状態が等しいか返す
    /// @complexity $O(1)$
    bool operator==(const Xorshift &rhs) noexcept { return (state == rhs.state); }

    /// @brief 状態が異なるか返す
    /// @complexity $O(1)$
    bool operator!=(const Xorshift &rhs) noexcept { return (state != rhs.state); }

    /// @brief 現在の状態を返す
    /// @complexity $O(1)$
    constexpr state_type serialize() const noexcept { return state; }

    /// @brief 保存した状態を復元する
    /// @complexity $O(1)$
    constexpr void deserialize(const state_type &data) noexcept { state = data; }

    /// @brief 保存した状態をmoveして復元する
    /// @complexity $O(1)$
    constexpr void deserialize(state_type &&data) noexcept { state = std::move(data); }

    /// @brief a以上b以下の整数を生成
    /// @return uint32_t [a, b]
    /// @complexity $O(1)$
    std::uint32_t rand_range(std::uint32_t a, std::uint32_t b) {
        if (a == Xorshift::min() && b == Xorshift::max()) return operator()();
        return a + operator()() % (b - a + 1);
    }

    /// @brief 0.0以上1.0未満の浮動小数点数を生成
    /// @return double [0, 1)
    /// @complexity $O(1)$
    double random() { return (double)operator()() / max(); }

  private:
    state_type state;
};
