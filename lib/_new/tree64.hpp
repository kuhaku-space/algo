#include "template/template.hpp"

template <int N, class D = void>
struct tree64 {
    static constexpr int C = calc_c(N);

    uint64_t map;
    array<tree64<C>, (N - 1) / C + 1> child;

    tree64() : map(0), child() {}

    constexpr int calc_c(int n) {
        int res = 1;
        while (n > 64) {
            res *= 64;
            n /= 64;
        }
        return res;
    }
    int bsf(const uint64_t x) { return __builtin_ctzll(x); }
    int bsr(const uint64_t x) { return 63 - __builtin_clzll(x); }

    bool insert(const int key) {
        const int pos = key / C;
        map |= 1ULL << pos;
        return child[pos].insert(key % C);
    }

    bool erase(const int key) {
        const int pos = key / C;
        const bool res = child[pos].erase(key % C);
        if (child[pos]._get_map() == 0) {
            map &= ~(1ULL << pos);
        }
        return res;
    }

    bool contains(const int key) const {
        return child[key / C].contains(key % C);
    }

    int min() const {
        const int pos = bsf(map);
        return pos * C + child[pos].min();
    }

    int max() const {
        const int pos = bsr(map);
        return pos * C + child[pos].max();
    }

    int pred(const int key) const {
        const int pos = key / C;
        const int t = child[pos].pred(key % C);
        if (t != -1) {
            return pos * C + t;
        }
        const uint64_t masked = map & ~(~0ULL << pos);
        if (masked == 0) {
            return -1;
        }
        const int pos2 = bsr(masked);
        return pos2 * C + child[pos2].max();
    }

    int succ(const int key) const {
        const int pos = key / C;
        const int t = child[pos].succ(key % C);
        if (t != -1) {
            return pos * C + t;
        }
        const uint64_t masked = map & ~(~0ULL >> (63 - pos));
        if (masked == 0) {
            return -1;
        }
        const int pos2 = bsf(masked);
        return pos2 * C + child[pos2].min();
    }

    uint64_t _get_map() const { return map; }
};

template <int N>
struct tree64<N, typename enable_if<(N <= 64)>::type> {
    uint64_t map;

    tree64() : map(0) {}

    int bsf(const uint64_t x) { return __builtin_ctzll(x); }
    int bsr(const uint64_t x) { return 63 - __builtin_clzll(x); }

    bool insert(const int key) {
        const uint64_t pop = 1ULL << key;
        if ((map & pop) != 0) {
            return false;
        } else {
            map |= pop;
            return true;
        }
    }

    bool erase(const int key) {
        const uint64_t pop = 1ULL << key;
        if ((map & pop) != 0) {
            map &= ~pop;
            return true;
        } else {
            return false;
        }
    }

    bool contains(const int key) const { return (map & 1ULL << key) != 0; }

    int min() const { return bsf(map); }

    int max() const { return bsr(map); }

    int pred(const int key) const {
        const uint64_t masked = map & ~(~0ULL << key);
        if (masked == 0) {
            return -1;
        }
        return bsr(masked);
    }

    int succ(const int key) const {
        const uint64_t masked = map & (~0ULL << key);
        if (masked == 0) {
            return -1;
        }
        return bsf(masked);
    }

    uint64_t _get_map() const { return map; }
};
