#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include "internal/internal_random.hpp"

/// @file
/// @brief 疑似乱数生成器 SplitMix64
/// @details 64 bit 整数を高速に生成する SplitMix64。単体の疑似乱数生成器として利用できるほか、
///          他の乱数生成器へ状態列を供給するシード生成器としても利用できる。

/// @brief 疑似乱数生成器 SplitMix64
/// @details 周期：$2^{64}$
/// @complexity すべての操作が $O(1)$、長さNのseed列生成は $O(N)$
struct SplitMix64 {
    /// @brief 内部状態の型
    /// @complexity 型エイリアスで実行時計算量はない
    using state_type = std::uint64_t;

    /// @brief 生成結果の型
    /// @complexity 型エイリアスで実行時計算量はない
    using result_type = std::uint64_t;

    /// @brief 既定seedで構築する
    /// @complexity $O(1)$
    constexpr SplitMix64() noexcept : state(1234567890) {}

    /// @brief 指定seedで構築する
    /// @complexity $O(1)$
    constexpr SplitMix64(std::uint64_t seed) noexcept : state(seed) {}

    /// @brief 生成しうる最小値を返す
    /// @complexity $O(1)$
    static constexpr result_type min() noexcept { return std::numeric_limits<result_type>::min(); }

    /// @brief 生成しうる最大値を返す
    /// @complexity $O(1)$
    static constexpr result_type max() noexcept { return std::numeric_limits<result_type>::max(); }

    /// @brief 次の64bit乱数を返す
    /// @complexity $O(1)$
    constexpr result_type operator()() noexcept {
        std::uint64_t z = (state += 0x9e3779b97f4a7c15);
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }

    /// @brief 状態が等しいか返す
    /// @complexity $O(1)$
    constexpr bool operator==(const SplitMix64 &) const noexcept = default;

    /// @brief 現在の状態を返す
    /// @complexity $O(1)$
    constexpr state_type serialize() const noexcept { return state; }

    /// @brief 保存した状態を復元する
    /// @complexity $O(1)$
    constexpr void deserialize(const state_type &data) noexcept { state = data; }

    /// @brief N個の64bit seedを生成する
    /// @complexity $O(N)$
    template <std::size_t N>
    constexpr std::array<std::uint64_t, N> generate_seed_sequence() noexcept {
        std::array<std::uint64_t, N> seeds = {};
        for (auto &seed : seeds) seed = operator()();
        return seeds;
    }

    /// @brief a以上b以下の整数を偏りなく生成する
    /// @return uint64_t [a, b]
    /// @complexity 期待 $O(1)$
    constexpr result_type rand_range(result_type a, result_type b) noexcept {
        return internal::uniform_int(*this, a, b);
    }

    /// @brief 0.0以上1.0未満の浮動小数点数を生成
    /// @return double [0, 1)
    /// @complexity $O(1)$
    constexpr double random() noexcept { return internal::uniform_real(*this); }

  private:
    state_type state;
};
