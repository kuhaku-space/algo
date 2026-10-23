#pragma once
#include <array>
#include <bit>
#include <cstdint>
#include "internal/internal_random.hpp"
#include "random/split_mix64.hpp"

/// @brief 疑似乱数生成器 xoroshiro128++
/// @complexity すべての操作が $O(1)$
struct Xoroshiro128 : internal::RandomEngineBase<Xoroshiro128, std::array<std::uint64_t, 2>, std::uint64_t> {
    /// @brief 既定seedで構築する
    /// @complexity $O(1)$
    constexpr Xoroshiro128() noexcept : RandomEngineBase(SplitMix64{}.generate_seed_sequence<2>()) {}

    /// @brief 指定seedで構築する
    /// @complexity $O(1)$
    constexpr Xoroshiro128(std::uint64_t seed) noexcept
        : RandomEngineBase(SplitMix64{seed}.generate_seed_sequence<2>()) {}

    /// @brief 次の64bit乱数を返す
    /// @complexity $O(1)$
    constexpr result_type operator()() noexcept {
        const std::uint64_t s0 = state[0];
        std::uint64_t s1 = state[1];
        const std::uint64_t result = std::rotl(s0 + s1, 17) + s0;
        s1 ^= s0;
        state[0] = std::rotl(s0, 49) ^ s1 ^ (s1 << 21), state[1] = std::rotl(s1, 28);
        return result;
    }
};
