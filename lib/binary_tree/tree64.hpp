#include <array>
#include <cstdint>
#include <type_traits>

namespace internal {

constexpr int bsf(const std::uint64_t x) { return __builtin_ctzll(x); }
constexpr int bsr(const std::uint64_t x) { return 63 - __builtin_clzll(x); }

constexpr int calc_c(int n) {
    int res = 1;
    while (n > 64) {
        res *= 64;
        n /= 64;
    }
    return res;
}

}  // namespace internal

template <int N>
struct tree64 {
    tree64() : map(0), child() {}

    bool insert(const int key) {
        const int pos = key / C;
        map |= 1ULL << pos;
        return child[pos].insert(key % C);
    }

    bool erase(const int key) {
        const int pos = key / C;
        const bool res = child[pos].erase(key % C);
        if (child[pos].get_map() == 0) map &= ~(1ULL << pos);
        return res;
    }

    bool contains(const int key) const { return child[key / C].contains(key % C); }

    int min() const {
        const int pos = internal::bsf(map);
        return pos * C + child[pos].min();
    }

    int max() const {
        const int pos = internal::bsr(map);
        return pos * C + child[pos].max();
    }

    int pred(const int key) const {
        const int pos = key / C;
        const int t = child[pos].pred(key % C);
        if (t != -1) { return pos * C + t; }
        const std::uint64_t masked = map & ~(~0ULL << pos);
        if (masked == 0) return -1;
        const int pos2 = internal::bsr(masked);
        return pos2 * C + child[pos2].max();
    }

    int succ(const int key) const {
        const int pos = key / C;
        const int t = child[pos].succ(key % C);
        if (t != -1) return pos * C + t;
        const std::uint64_t masked = map & ~(~0ULL >> (63 - pos));
        if (masked == 0) return -1;
        const int pos2 = internal::bsf(masked);
        return pos2 * C + child[pos2].min();
    }

    std::uint64_t get_map() const { return map; }

  private:
    static constexpr int C = internal::calc_c(N);

    std::uint64_t map;
    std::array<tree64<C>, (N - 1) / C + 1> child;
};

template <int N>
requires(N <= 64) struct tree64<N> {
    tree64() : map(0) {}

    bool insert(const int key) {
        const std::uint64_t pop = 1ULL << key;
        if ((map & pop) != 0) {
            return false;
        } else {
            map |= pop;
            return true;
        }
    }

    bool erase(const int key) {
        const std::uint64_t pop = 1ULL << key;
        if ((map & pop) != 0) {
            map &= ~pop;
            return true;
        } else {
            return false;
        }
    }

    bool contains(const int key) const { return (map & 1ULL << key) != 0; }

    int min() const { return internal::bsf(map); }

    int max() const { return internal::bsr(map); }

    int pred(const int key) const {
        const std::uint64_t masked = map & ~(~0ULL << key);
        if (masked == 0) return -1;
        return internal::bsr(masked);
    }

    int succ(const int key) const {
        const std::uint64_t masked = map & (~0ULL << key);
        if (masked == 0) return -1;
        return internal::bsf(masked);
    }

    std::uint64_t get_map() const { return map; }

  private:
    std::uint64_t map;
};
