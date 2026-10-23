#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include "internal/internal_random.hpp"

/// @file
/// @brief 疑似乱数生成器 SplitMix64
/// @details 64 bit 整数を高速に生成する SplitMix64。単体の疑似乱数生成器として利用できるほか、
///          他の乱数生成器へ状態列を供給するシード生成器としても利用できる。

/// @brief 疑似乱数生成器 SplitMix64
/// @details 周期：$2^{64}$
/// @complexity すべての操作が $O(1)$、長さNのseed列生成は $O(N)$
struct SplitMix64 : internal::RandomEngineBase<SplitMix64, std::uint64_t, std::uint64_t> {
    /// @brief 既定seedで構築する
    /// @complexity $O(1)$
    constexpr SplitMix64() noexcept : RandomEngineBase(1234567890) {}

    /// @brief 指定seedで構築する
    /// @complexity $O(1)$
    constexpr SplitMix64(std::uint64_t seed) noexcept : RandomEngineBase(seed) {}

    /// @brief 次の64bit乱数を返す
    /// @complexity $O(1)$
    constexpr result_type operator()() noexcept {
        std::uint64_t z = (state += 0x9e3779b97f4a7c15);
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }

    /// @brief N個の64bit seedを生成する
    /// @complexity $O(N)$
    template <std::size_t N>
    constexpr std::array<std::uint64_t, N> generate_seed_sequence() noexcept {
        std::array<std::uint64_t, N> seeds = {};
        for (auto &seed : seeds) seed = operator()();
        return seeds;
    }
};
