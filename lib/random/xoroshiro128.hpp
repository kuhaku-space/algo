#pragma once
#include <array>
#include <bit>
#include <cstdint>
#include <limits>
#include <utility>
#include "random/split_mix_64.hpp"

/// @brief 疑似乱数生成器 xoroshiro128++
struct xoroshiro128 {
    using state_type = std::array<std::uint64_t, 2>;
    using result_type = std::uint64_t;

    constexpr xoroshiro128() noexcept : state(split_mix_64{}.generate_seed_sequence<2>()) {}
    constexpr xoroshiro128(std::uint64_t seed) noexcept : state(split_mix_64{seed}.generate_seed_sequence<2>()) {}

    static constexpr result_type min() noexcept { return std::numeric_limits<result_type>::min(); }
    static constexpr result_type max() noexcept { return std::numeric_limits<result_type>::max(); }
    constexpr result_type operator()() {
        const std::uint64_t s0 = state[0];
        std::uint64_t s1 = state[1];
        const std::uint64_t result = std::rotl(s0 + s1, 17) + s0;
        s1 ^= s0;
        state[0] = std::rotl(s0, 49) ^ s1 ^ (s1 << 21), state[1] = std::rotl(s1, 28);
        return result;
    }
    bool operator==(const xoroshiro128 &rhs) noexcept { return (state == rhs.state); }
    bool operator!=(const xoroshiro128 &rhs) noexcept { return (state != rhs.state); }

    constexpr state_type serialize() const noexcept { return state; }
    constexpr void deserialize(const state_type &data) noexcept { state = data; }
    constexpr void deserialize(state_type &&data) noexcept { state = std::move(data); }

    /// @brief a以上b以下の整数を生成
    /// @return uint64_t [a, b]
    std::uint64_t rand_range(std::uint64_t a, std::uint64_t b) {
        if (a == xoroshiro128::min() && b == xoroshiro128::max()) return operator()();
        return a + operator()() % (b - a + 1);
    }

    /// @brief 0.0以上1.0未満の浮動小数点数を生成
    /// @return double [0, 1)
    double random() noexcept { return (double)operator()() / max(); }

  private:
    state_type state;
};
