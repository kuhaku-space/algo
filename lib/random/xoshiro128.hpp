#pragma once
#include <array>
#include <cstdint>
#include <limits>
#include <utility>
#include "random/split_mix_64.hpp"

/// @brief 疑似乱数生成器 xoshiro128++
struct xoshiro128 {
    using state_type = std::array<std::uint32_t, 4>;
    using result_type = std::uint32_t;

    constexpr xoshiro128() : state() {
        split_mix_64 split_mix{};
        for (auto &s : state) s = static_cast<std::uint32_t>(split_mix());
    }
    constexpr xoshiro128(std::uint64_t seed) noexcept : state() {
        split_mix_64 split_mix{seed};
        for (auto &s : state) s = static_cast<std::uint32_t>(split_mix());
    }

    static constexpr result_type min() noexcept { return std::numeric_limits<result_type>::min(); }
    static constexpr result_type max() noexcept { return std::numeric_limits<result_type>::max(); }
    constexpr result_type operator()() {
        const std::uint32_t result = rotl(state[0] + state[3], 7) + state[0];
        const std::uint32_t t = state[1] << 9;
        state[2] ^= state[0];
        state[3] ^= state[1];
        state[1] ^= state[2];
        state[0] ^= state[3];
        state[2] ^= t;
        state[3] = rotl(state[3], 11);
        return result;
    }
    bool operator==(const xoshiro128 &rhs) noexcept { return (state == rhs.state); }
    bool operator!=(const xoshiro128 &rhs) noexcept { return (state != rhs.state); }

    constexpr state_type serialize() const noexcept { return state; }
    constexpr void deserialize(const state_type &data) noexcept { state = data; }
    constexpr void deserialize(state_type &&data) noexcept { state = std::move(data); }

    /// @brief a以上b以下の整数を生成
    /// @return int [a, b]
    int rand_range(std::uint32_t a, std::uint32_t b) {
        if (a == xoshiro128::min() && b == xoshiro128::max()) return operator()();
        return a + operator()() % (b - a + 1);
    }

    /// @brief 0.0以上1.0未満の浮動小数点数を生成
    /// @return double [0, 1)
    double random() { return (double)operator()() / max(); }

  private:
    state_type state;

    static constexpr std::uint32_t rotl(const std::uint32_t x, const int s) noexcept {
        return (x << s) | (x >> (32 - s));
    }
};
