#pragma once
#include <array>
#include <cstdint>
#include <limits>
#include <utility>

/// @brief 疑似乱数生成器 SplitMix64
/// @details 周期：$2^64-1$
/// @complexity すべての操作が $O(1)$、長さNのseed列生成は $O(N)$
struct split_mix_64 {
    /// @brief 内部状態の型
    /// @complexity 型エイリアスで実行時計算量はない
    using state_type = std::uint64_t;

    /// @brief 生成結果の型
    /// @complexity 型エイリアスで実行時計算量はない
    using result_type = std::uint64_t;

    /// @brief 既定seedで構築する
    /// @complexity $O(1)$
    constexpr split_mix_64() noexcept : state(1234567890) {}

    /// @brief 指定seedで構築する
    /// @complexity $O(1)$
    constexpr split_mix_64(std::uint64_t seed) noexcept : state(seed) {}

    /// @brief 生成しうる最小値を返す
    /// @complexity $O(1)$
    static constexpr result_type min() noexcept { return std::numeric_limits<result_type>::min(); }

    /// @brief 生成しうる最大値を返す
    /// @complexity $O(1)$
    static constexpr result_type max() noexcept { return std::numeric_limits<result_type>::max(); }

    /// @brief 次の64bit乱数を返す
    /// @complexity $O(1)$
    constexpr result_type operator()() {
        std::uint64_t z = (state += 0x9e3779b97f4a7c15);
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }

    /// @brief 現在の状態を返す
    /// @complexity $O(1)$
    constexpr state_type serialize() const noexcept { return state; }

    /// @brief 保存した状態を復元する
    /// @complexity $O(1)$
    constexpr void deserialize(const state_type &data) noexcept { state = data; }

    /// @brief 保存した状態をmoveして復元する
    /// @complexity $O(1)$
    constexpr void deserialize(state_type &&data) noexcept { state = std::move(data); }

    /// @brief N個の64bit seedを生成する
    /// @complexity $O(N)$
    template <std::size_t N>
    constexpr std::array<std::uint64_t, N> generate_seed_sequence() noexcept {
        std::array<std::uint64_t, N> seeds = {};
        for (auto &seed : seeds) seed = operator()();
        return seeds;
    }

    /// @brief a以上b以下の整数を生成
    /// @return uint64_t [a, b]
    /// @complexity $O(1)$
    std::uint64_t rand_range(std::uint64_t a, std::uint64_t b) {
        if (a == split_mix_64::min() && b == split_mix_64::max()) return operator()();
        return a + operator()() % (b - a + 1);
    }

    /// @brief 0.0以上1.0未満の浮動小数点数を生成
    /// @return double [0, 1)
    /// @complexity $O(1)$
    double random() { return (double)operator()() / max(); }

  private:
    state_type state;
};
