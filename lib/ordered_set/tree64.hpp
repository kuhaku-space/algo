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
template <int N>
struct Tree64 {
    Tree64() : map(0), child() {}

    bool insert(const int key) {
        const int pos = key >> shift;
        map |= 1ull << pos;
        return child[pos].insert(key & mask);
    }

    bool erase(const int key) {
        const int pos = key >> shift;
        const bool res = child[pos].erase(key & mask);
        if (child[pos].get_map() == 0) map &= ~(1ull << pos);
        return res;
    }

    bool contains(const int key) const { return child[key >> shift].contains(key & mask); }

    int min() const {
        const int pos = std::countr_zero(map);
        return (pos << shift) + child[pos].min();
    }

    int max() const {
        const int pos = std::bit_width(map) - 1;
        return (pos << shift) + child[pos].max();
    }

    int pred(const int key) const {
        const int pos = key >> shift;
        const int t = child[pos].pred(key & mask);
        if (t != -1) { return (pos << shift) + t; }
        const std::uint64_t masked = map & ~(~0ULL << pos);
        if (masked == 0) return -1;
        const int pos2 = std::bit_width(masked) - 1;
        return (pos2 << shift) + child[pos2].max();
    }

    int succ(const int key) const {
        const int pos = key >> shift;
        const int t = child[pos].succ(key & mask);
        if (t != -1) return (pos << shift) + t;
        const std::uint64_t masked = map & ~(~0ULL >> (63 - pos));
        if (masked == 0) return -1;
        const int pos2 = std::countr_zero(masked);
        return (pos2 << shift) + child[pos2].min();
    }

    std::uint64_t get_map() const { return map; }

  private:
    static constexpr int C = internal::calc_c(N);
    static constexpr int shift = std::countr_zero(static_cast<unsigned>(C));
    static constexpr int mask = C - 1;

    std::uint64_t map;
    std::array<Tree64<C>, (N - 1) / C + 1> child;
};

template <int N>
requires(N <= 64)
struct Tree64<N> {
    Tree64() : map(0) {}

    bool insert(const int key) {
        const std::uint64_t pop = 1ull << key;
        if ((map & pop) != 0) {
            return false;
        } else {
            map |= pop;
            return true;
        }
    }

    bool erase(const int key) {
        const std::uint64_t pop = 1ull << key;
        if ((map & pop) != 0) {
            map &= ~pop;
            return true;
        } else {
            return false;
        }
    }

    bool contains(const int key) const { return (map & 1ull << key) != 0; }

    int min() const { return std::countr_zero(map); }

    int max() const { return std::bit_width(map) - 1; }

    int pred(const int key) const {
        const std::uint64_t masked = map & ~(~0ULL << key);
        if (masked == 0) return -1;
        return std::bit_width(masked) - 1;
    }

    int succ(const int key) const {
        const std::uint64_t masked = map & (~0ULL << key);
        if (masked == 0) return -1;
        return std::countr_zero(masked);
    }

    std::uint64_t get_map() const { return map; }

  private:
    std::uint64_t map;
};
