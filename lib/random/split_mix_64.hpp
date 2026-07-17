#pragma once
#include <array>
#include <cstdint>
#include <limits>
#include <utility>

/**
 * @brief 疑似乱数生成器 SplitMix64
 * @details 周期：$2^64-1$
 */
struct split_mix_64 {
    using state_type = std::uint64_t;
    using result_type = std::uint64_t;

    constexpr split_mix_64() noexcept : state(1234567890) {}
    constexpr split_mix_64(std::uint64_t seed) noexcept : state(seed) {}

    static constexpr result_type min() noexcept { return std::numeric_limits<result_type>::min(); }
    static constexpr result_type max() noexcept { return std::numeric_limits<result_type>::max(); }
    constexpr result_type operator()() {
        std::uint64_t z = (state += 0x9e3779b97f4a7c15);
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }

    constexpr state_type serialize() const noexcept { return state; }
    constexpr void deserialize(const state_type &data) noexcept { state = data; }
    constexpr void deserialize(state_type &&data) noexcept { state = std::move(data); }

    template <std::size_t N>
    constexpr std::array<std::uint64_t, N> generate_seed_sequence() noexcept {
        std::array<std::uint64_t, N> seeds = {};
        for (auto &seed : seeds) seed = operator()();
        return seeds;
    }

    /// @brief a以上b以下の整数を生成
    /// @return uint64_t [a, b]
    std::uint64_t rand_range(std::uint64_t a, std::uint64_t b) {
        if (a == split_mix_64::min() && b == split_mix_64::max()) return operator()();
        return a + operator()() % (b - a + 1);
    }

    /// @brief 0.0以上1.0未満の浮動小数点数を生成
    /// @return double [0, 1)
    double random() { return (double)operator()() / max(); }

  private:
    state_type state;
};
