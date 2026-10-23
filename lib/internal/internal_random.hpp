#pragma once
#include <concepts>
#include <cstdint>
#include <limits>
#include <random>
#include <type_traits>

namespace internal {

/// @brief `result_type` の全範囲（32 bit か 64 bit）を一様に返す乱数生成器
template <class G>
concept random_engine_32_or_64 = std::uniform_random_bit_generator<G> && G::min() == 0 &&
                                 G::max() == std::numeric_limits<typename G::result_type>::max() &&
                                 (std::numeric_limits<typename G::result_type>::digits == 32 ||
                                  std::numeric_limits<typename G::result_type>::digits == 64);

/// @brief `gen` から a 以上 b 以下の整数を偏りなく生成する（Lemire の方法）
/// @complexity 期待 $O(1)$
template <random_engine_32_or_64 G>
constexpr G::result_type uniform_int(G &gen, typename G::result_type a, typename G::result_type b) {
    using result_type = G::result_type;
    constexpr int digits = std::numeric_limits<result_type>::digits;
    using wide_type = std::conditional_t<digits == 32, std::uint64_t, unsigned __int128>;
    if (a == G::min() && b == G::max()) return gen();
    const result_type s = b - a + 1;
    wide_type m = wide_type(gen()) * s;
    if (result_type(m) < s) {
        const result_type threshold = result_type(-s) % s;
        while (result_type(m) < threshold) m = wide_type(gen()) * s;
    }
    return a + result_type(m >> digits);
}

/// @brief `gen` から 0.0 以上 1.0 未満の浮動小数点数を生成する
/// @complexity $O(1)$
template <random_engine_32_or_64 G>
constexpr double uniform_real(G &gen) {
    if constexpr (std::numeric_limits<typename G::result_type>::digits == 64) return (gen() >> 11) * 0x1.0p-53;
    else return gen() * 0x1.0p-32;
}

}  // namespace internal
