#pragma once
#include <array>
#include <cstdint>
#include "internal/internal_random.hpp"
#include "random/split_mix64.hpp"

/// @brief 疑似乱数生成器 xorshift128
/// @complexity すべての操作が $O(1)$
struct Xorshift128 : internal::RandomEngineBase<Xorshift128, std::array<std::uint32_t, 4>, std::uint32_t> {
    /// @brief 既定seedで構築する
    /// @complexity $O(1)$
    constexpr Xorshift128() noexcept : RandomEngineBase({123456789, 362436069, 521288629, 88675123}) {}

    /// @brief 指定seedで構築する
    /// @complexity $O(1)$
    constexpr Xorshift128(std::uint64_t seed) noexcept : RandomEngineBase({}) {
        SplitMix64 split_mix{seed};
        for (auto &s : state) s = static_cast<std::uint32_t>(split_mix());
    }

    /// @brief 次の32bit乱数を返す
    /// @complexity $O(1)$
    constexpr result_type operator()() noexcept {
        std::uint32_t t = (state[0] ^ (state[0] << 11));
        state[0] = state[1], state[1] = state[2], state[2] = state[3];
        return state[3] = (state[3] ^ (state[3] >> 19)) ^ (t ^ (t >> 8));
    }
};
