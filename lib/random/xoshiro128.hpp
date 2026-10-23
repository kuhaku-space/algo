#pragma once
#include <array>
#include <bit>
#include <cstdint>
#include "internal/internal_random.hpp"
#include "random/split_mix64.hpp"

/// @brief 疑似乱数生成器 xoshiro128++
/// @complexity すべての操作が $O(1)$
struct Xoshiro128 : internal::RandomEngineBase<Xoshiro128, std::array<std::uint32_t, 4>, std::uint32_t> {
    /// @brief 既定seedで構築する
    /// @complexity $O(1)$
    constexpr Xoshiro128() noexcept : RandomEngineBase({}) {
        SplitMix64 split_mix{};
        for (auto &s : state) s = static_cast<std::uint32_t>(split_mix());
    }

    /// @brief 指定seedで構築する
    /// @complexity $O(1)$
    constexpr Xoshiro128(std::uint64_t seed) noexcept : RandomEngineBase({}) {
        SplitMix64 split_mix{seed};
        for (auto &s : state) s = static_cast<std::uint32_t>(split_mix());
    }

    /// @brief 次の32bit乱数を返す
    /// @complexity $O(1)$
    constexpr result_type operator()() noexcept {
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
};
