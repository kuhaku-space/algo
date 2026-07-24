#pragma once
#include <concepts>
#include <functional>
#include <random>
#include <unordered_map>
#include "random/xoroshiro128.hpp"

namespace internal {

template <typename T>
concept Hashable = std::equality_comparable<T> && requires(const T &a) {
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
};

}  // namespace internal

/// @brief Zobrist ハッシュ
/// @details 値ごとに独立な乱数を割り当てて記憶する。複数の値の合成は用途に応じて呼び出し側が選ぶ。
///          - 総和で合成（`Add<result_type>` 相当）: 多重集合のハッシュ。同じ値が複数回現れても
///            打ち消し合わず区別できる（木の同型判定など、部分木の多重集合を比較する場面向き）。
///          - XOR で合成（`Xor<result_type>` 相当）: 集合の要素の有無を表すハッシュ。
///            同じ値をもう一度 XOR すれば打ち消せるため要素の追加・削除を O(1) で反映できるが、
///            同じ値が偶数回現れると消えてしまうため多重集合の区別には使えない。
/// @tparam T 値の型（Hashable であること）
/// @tparam UniformRandomBitGenerator 乱数生成器
/// @complexity 値ごとの取得は期待 $O(1)$
template <internal::Hashable T, std::uniform_random_bit_generator UniformRandomBitGenerator = xoroshiro128>
struct ZobristHash {
    /// @brief ハッシュ値の型
    /// @complexity 型エイリアスで実行時計算量はない
    using result_type = UniformRandomBitGenerator::result_type;

    /// @brief 空の対応表を乱数seed付きで構築する
    /// @complexity O(1)
    ZobristHash() : rnd(std::random_device{}()), data() {}

    /// @brief 値 x に割り当てられた乱数を返す（初回はその場で割り当てて記憶する）
    /// @complexity 期待 O(1)
    result_type operator()(const T &x) {
        auto [it, inserted] = data.try_emplace(x);
        if (inserted) it->second = rnd();
        return it->second;
    }

  private:
    UniformRandomBitGenerator rnd;
    std::unordered_map<T, result_type> data;
};
