#pragma once
#include <array>
#include <bit>
#include <cassert>
#include <cstdint>
#include <type_traits>

namespace internal {

constexpr int calc_c(int n) {
    int res = 1;
    while (n > 64) res *= 64, n /= 64;
    return res;
}

}  // namespace internal

/// @brief 64分木
/// @complexity 各操作 $O(\log_{64}N)$
template <int N>
struct Tree64 {
    /// @brief 空集合を構築する
    /// @complexity $O(\log_{64}N)$
    Tree64() : map(0), child() {}

    /// @brief keyを挿入し、新規挿入ならtrueを返す
    /// @complexity $O(\log_{64}N)$
    bool insert(const int key) {
        const int pos = key >> shift;
        map |= 1ull << pos;
        return child[pos].insert(key & mask);
    }

    /// @brief keyを削除し、存在したならtrueを返す
    /// @complexity $O(\log_{64}N)$
    bool erase(const int key) {
        const int pos = key >> shift;
        const bool res = child[pos].erase(key & mask);
        if (child[pos].get_map() == 0) map &= ~(1ull << pos);
        return res;
    }

    /// @brief keyを含むか返す
    /// @complexity $O(\log_{64}N)$
    bool contains(const int key) const { return child[key >> shift].contains(key & mask); }

    /// @brief 最小要素を返す
    /// @complexity $O(\log_{64}N)$
    int min() const {
        const int pos = std::countr_zero(map);
        return (pos << shift) + child[pos].min();
    }

    /// @brief 最大要素を返す
    /// @complexity $O(\log_{64}N)$
    int max() const {
        const int pos = std::bit_width(map) - 1;
        return (pos << shift) + child[pos].max();
    }

    /// @brief key未満で最大の要素を返し、無ければ-1を返す
    /// @complexity $O(\log_{64}N)$
    int pred(const int key) const {
        const int pos = key >> shift;
        const int t = child[pos].pred(key & mask);
        if (t != -1) { return (pos << shift) + t; }
        const std::uint64_t masked = map & ~(~0ULL << pos);
        if (masked == 0) return -1;
        const int pos2 = std::bit_width(masked) - 1;
        return (pos2 << shift) + child[pos2].max();
    }

    /// @brief key以上で最小の要素を返し、無ければ-1を返す
    /// @complexity $O(\log_{64}N)$
    int succ(const int key) const {
        const int pos = key >> shift;
        const int t = child[pos].succ(key & mask);
        if (t != -1) return (pos << shift) + t;
        const std::uint64_t masked = map & ~(~0ULL >> (63 - pos));
        if (masked == 0) return -1;
        const int pos2 = std::countr_zero(masked);
        return (pos2 << shift) + child[pos2].min();
    }

    /// @brief 直下の子が空でないことを表すbit maskを返す
    /// @complexity $O(1)$
    std::uint64_t get_map() const { return map; }

  private:
    static constexpr int C = internal::calc_c(N);
    static constexpr int shift = std::countr_zero(static_cast<unsigned>(C));
    static constexpr int mask = C - 1;

    std::uint64_t map;
    std::array<Tree64<C>, (N - 1) / C + 1> child;
};

/// @brief 64要素以下のTree64終端層
/// @complexity すべての操作が $O(1)$
template <int N>
requires(N <= 64)
struct Tree64<N> {
    /// @brief 空集合を構築する
    /// @complexity $O(1)$
    Tree64() : map(0) {}

    /// @brief keyを挿入し、新規挿入ならtrueを返す
    /// @complexity $O(1)$
    bool insert(const int key) {
        const std::uint64_t pop = 1ull << key;
        if ((map & pop) != 0) {
            return false;
        } else {
            map |= pop;
            return true;
        }
    }

    /// @brief keyを削除し、存在したならtrueを返す
    /// @complexity $O(1)$
    bool erase(const int key) {
        const std::uint64_t pop = 1ull << key;
        if ((map & pop) != 0) {
            map &= ~pop;
            return true;
        } else {
            return false;
        }
    }

    /// @brief keyを含むか返す
    /// @complexity $O(1)$
    bool contains(const int key) const { return (map & 1ull << key) != 0; }

    /// @brief 最小要素を返す
    /// @complexity $O(1)$
    int min() const { return std::countr_zero(map); }

    /// @brief 最大要素を返す
    /// @complexity $O(1)$
    int max() const { return std::bit_width(map) - 1; }

    /// @brief key未満で最大の要素を返し、無ければ-1を返す
    /// @complexity $O(1)$
    int pred(const int key) const {
        const std::uint64_t masked = map & ~(~0ULL << key);
        if (masked == 0) return -1;
        return std::bit_width(masked) - 1;
    }

    /// @brief key以上で最小の要素を返し、無ければ-1を返す
    /// @complexity $O(1)$
    int succ(const int key) const {
        const std::uint64_t masked = map & (~0ULL << key);
        if (masked == 0) return -1;
        return std::countr_zero(masked);
    }

    /// @brief 要素集合をbit maskで返す
    /// @complexity $O(1)$
    std::uint64_t get_map() const { return map; }

  private:
    std::uint64_t map;
};
