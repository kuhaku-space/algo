#pragma once
#include <array>
#include <bit>
#include <cstdint>
#include <limits>
#include <utility>
#include "random/split_mix_64.hpp"

/// @brief 疑似乱数生成器 xoroshiro128++
/// @complexity すべての操作が $O(1)$
struct xoroshiro128 {
    /// @brief 内部状態の型
    /// @complexity 型エイリアスで実行時計算量はない
    using state_type = std::array<std::uint64_t, 2>;

    /// @brief 生成結果の型
    /// @complexity 型エイリアスで実行時計算量はない
    using result_type = std::uint64_t;

    /// @brief 既定seedで構築する
    /// @complexity $O(1)$
    constexpr xoroshiro128() noexcept : state(split_mix_64{}.generate_seed_sequence<2>()) {}

    /// @brief 指定seedで構築する
    /// @complexity $O(1)$
    constexpr xoroshiro128(std::uint64_t seed) noexcept : state(split_mix_64{seed}.generate_seed_sequence<2>()) {}

    /// @brief 生成しうる最小値を返す
    /// @complexity $O(1)$
    static constexpr result_type min() noexcept { return std::numeric_limits<result_type>::min(); }

    /// @brief 生成しうる最大値を返す
    /// @complexity $O(1)$
    static constexpr result_type max() noexcept { return std::numeric_limits<result_type>::max(); }

    /// @brief 次の64bit乱数を返す
    /// @complexity $O(1)$
    constexpr result_type operator()() {
        const std::uint64_t s0 = state[0];
        std::uint64_t s1 = state[1];
        const std::uint64_t result = std::rotl(s0 + s1, 17) + s0;
        s1 ^= s0;
        state[0] = std::rotl(s0, 49) ^ s1 ^ (s1 << 21), state[1] = std::rotl(s1, 28);
        return result;
    }

    /// @brief 状態が等しいか返す
    /// @complexity $O(1)$
    bool operator==(const xoroshiro128 &rhs) noexcept { return (state == rhs.state); }

    /// @brief 状態が異なるか返す
    /// @complexity $O(1)$
    bool operator!=(const xoroshiro128 &rhs) noexcept { return (state != rhs.state); }

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
    /// @return uint64_t [a, b]
    /// @complexity $O(1)$
    std::uint64_t rand_range(std::uint64_t a, std::uint64_t b) {
        if (a == xoroshiro128::min() && b == xoroshiro128::max()) return operator()();
        return a + operator()() % (b - a + 1);
    }

    /// @brief 0.0以上1.0未満の浮動小数点数を生成
    /// @return double [0, 1)
    /// @complexity $O(1)$
    double random() noexcept { return (double)operator()() / max(); }

  private:
    state_type state;
};
