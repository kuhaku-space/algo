#pragma once
#include <array>
#include <cstdint>
#include <limits>
#include <utility>

/// @brief 擬似乱数生成器 Xorshift
struct Xorshift {
    using state_type = std::array<std::uint32_t, 4>;
    using result_type = std::uint32_t;
    constexpr Xorshift() : state{123456789, 362436069, 521288629, 88675123} {}

    static constexpr result_type min() { return std::numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }
    result_type operator()() {
        std::uint32_t t = (state[0] ^ (state[0] << 11));
        state[0] = state[1], state[1] = state[2], state[2] = state[3];
        return state[3] = (state[3] ^ (state[3] >> 19)) ^ (t ^ (t >> 8));
    }
    bool operator==(const Xorshift &rhs) noexcept { return (state == rhs.state); }
    bool operator!=(const Xorshift &rhs) noexcept { return (state != rhs.state); }

    constexpr state_type serialize() const noexcept { return state; }
    constexpr void deserialize(const state_type &data) noexcept { state = data; }
    constexpr void deserialize(state_type &&data) noexcept { state = std::move(data); }

    /// @brief a以上b以下の整数を生成
    /// @return uint32_t [a, b]
    std::uint32_t rand_range(std::uint32_t a, std::uint32_t b) {
        if (a == Xorshift::min() && b == Xorshift::max()) return operator()();
        return a + operator()() % (b - a + 1);
    }

    /// @brief 0.0以上1.0未満の浮動小数点数を生成
    /// @return double [0, 1)
    double random() { return (double)operator()() / max(); }

  private:
    state_type state;
};
