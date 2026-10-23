#pragma once
#include <concepts>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace internal {

/// @brief 疑似乱数生成器の共通部分（CRTP）
/// @details 派生型は `constexpr result_type operator()()` で `state` を進めて値を返す。
/// @tparam Derived 派生型
/// @tparam State 内部状態の型
/// @tparam Result 生成結果の型（32 bit か 64 bit の符号なし整数）
template <class Derived, class State, std::unsigned_integral Result>
requires(std::numeric_limits<Result>::digits == 32 || std::numeric_limits<Result>::digits == 64)
struct RandomEngineBase {
    /// @brief 内部状態の型
    /// @complexity 型エイリアスで実行時計算量はない
    using state_type = State;

    /// @brief 生成結果の型
    /// @complexity 型エイリアスで実行時計算量はない
    using result_type = Result;

    /// @brief 生成しうる最小値を返す
    /// @complexity $O(1)$
    static constexpr result_type min() noexcept { return std::numeric_limits<result_type>::min(); }

    /// @brief 生成しうる最大値を返す
    /// @complexity $O(1)$
    static constexpr result_type max() noexcept { return std::numeric_limits<result_type>::max(); }

    /// @brief 状態が等しいか返す
    /// @complexity $O(1)$
    constexpr bool operator==(const RandomEngineBase &) const noexcept = default;

    /// @brief 現在の状態を返す
    /// @complexity $O(1)$
    constexpr state_type serialize() const noexcept { return state; }

    /// @brief 保存した状態を復元する
    /// @complexity $O(1)$
    constexpr void deserialize(const state_type &data) noexcept { state = data; }

    /// @brief a以上b以下の整数を偏りなく生成する（Lemire の方法）
    /// @return result_type [a, b]
    /// @complexity 期待 $O(1)$
    constexpr result_type rand_range(result_type a, result_type b) noexcept {
        constexpr int digits = std::numeric_limits<result_type>::digits;
        using wide_type = std::conditional_t<digits == 32, std::uint64_t, unsigned __int128>;
        if (a == min() && b == max()) return generate();
        const result_type s = b - a + 1;
        wide_type m = wide_type(generate()) * s;
        if (result_type(m) < s) {
            const result_type threshold = result_type(-s) % s;
            while (result_type(m) < threshold) m = wide_type(generate()) * s;
        }
        return a + result_type(m >> digits);
    }

    /// @brief 0.0以上1.0未満の浮動小数点数を生成
    /// @return double [0, 1)
    /// @complexity $O(1)$
    constexpr double random() noexcept {
        if constexpr (std::numeric_limits<result_type>::digits == 64) return (generate() >> 11) * 0x1.0p-53;
        else return generate() * 0x1.0p-32;
    }

  protected:
    state_type state;

    constexpr RandomEngineBase(const state_type &_state) noexcept : state(_state) {}

  private:
    constexpr result_type generate() noexcept { return static_cast<Derived &>(*this)(); }
};

}  // namespace internal
