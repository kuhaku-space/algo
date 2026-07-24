#pragma once
#include <array>
#include <bit>
#include <cstdint>
#include <limits>
#include <utility>
#include "random/split_mix_64.hpp"

/// @brief 疑似乱数生成器 xoshiro128++
/// @complexity すべての操作が $O(1)$
struct xoshiro128 {
    /// @brief 内部状態の型
    /// @complexity 型エイリアスで実行時計算量はない
    using state_type = std::array<std::uint32_t, 4>;

    /// @brief 生成結果の型
    /// @complexity 型エイリアスで実行時計算量はない
    using result_type = std::uint32_t;

    /// @brief 既定seedで構築する
    /// @complexity $O(1)$
    constexpr xoshiro128() : state() {
        split_mix_64 split_mix{};
        for (auto &s : state) s = static_cast<std::uint32_t>(split_mix());
    }

    /// @brief 指定seedで構築する
    /// @complexity $O(1)$
    constexpr xoshiro128(std::uint64_t seed) noexcept : state() {
        split_mix_64 split_mix{seed};
        for (auto &s : state) s = static_cast<std::uint32_t>(split_mix());
    }

    /// @brief 生成しうる最小値を返す
    /// @complexity $O(1)$
    static constexpr result_type min() noexcept { return std::numeric_limits<result_type>::min(); }

    /// @brief 生成しうる最大値を返す
    /// @complexity $O(1)$
    static constexpr result_type max() noexcept { return std::numeric_limits<result_type>::max(); }

    /// @brief 次の32bit乱数を返す
    /// @complexity $O(1)$
    constexpr result_type operator()() {
        const std::uint32_t result = std::rotl(state[0] + state[3], 7) + state[0];
        const std::uint32_t t = state[1] << 9;
        state[2] ^= state[0];
        state[3] ^= state[1];
        state[1] ^= state[2];
        state[0] ^= state[3];
        state[2] ^= t;
        state[3] = std::rotl(state[3], 11);
        return result;
    }

    /// @brief 状態が等しいか返す
    /// @complexity $O(1)$
    bool operator==(const xoshiro128 &rhs) noexcept { return (state == rhs.state); }

    /// @brief 状態が異なるか返す
    /// @complexity $O(1)$
    bool operator!=(const xoshiro128 &rhs) noexcept { return (state != rhs.state); }

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
        if (a == xoshiro128::min() && b == xoshiro128::max()) return operator()();
        return a + operator()() % (b - a + 1);
    }

    /// @brief 0.0以上1.0未満の浮動小数点数を生成
    /// @return double [0, 1)
    /// @complexity $O(1)$
    double random() { return (double)operator()() / max(); }

  private:
    state_type state;
};
