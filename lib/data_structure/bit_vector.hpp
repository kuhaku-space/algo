#include "template/template.hpp"

/**
 * @brief 完備辞書
 *
 * @see https://ei1333.github.io/library/structure/wavelet/succinct-indexable-dictionary.hpp
 */
struct bit_vector {
    bit_vector() = default;
    bit_vector(unsigned int _length)
        : length(_length), blocks((_length + 31) >> 5), bit((_length + 31) >> 5),
          sum((_length + 31) >> 5) {}

    void set(unsigned int k) { bit[k >> 5] |= 1U << (k & 31); }

    void build() {
        sum[0] = 0U;
        for (unsigned int i = 1; i < blocks; ++i) {
            sum[i] = sum[i - 1] + __builtin_popcount(bit[i - 1]);
        }
    }

    bool operator[](unsigned int k) const { return bit[k >> 5] >> (k & 31) & 1; }

    unsigned int rank(unsigned int k) const {
        return sum[k >> 5] + __builtin_popcount(bit[k >> 5] & ((1U << (k & 31)) - 1));
    }
    unsigned int rank(bool val, unsigned int k) const { return val ? rank(k) : k - rank(k); }

    unsigned int select(unsigned int k) const {
        unsigned int sl = 0, sr = blocks + 1;
        while (sr - sl > 1) {
            unsigned int m = (sl + sr) >> 1;
            if (sum[m] < k) sl = m;
            else sr = m;
        }
        k -= sum[sl];
        unsigned int bl = 0, br = 32;
        while (br - bl > 1) {
            unsigned int m = (bl + br) >> 1;
            if (__builtin_popcount(bit[sl] & ((1U << m) - 1)) < k) bl = m;
            else br = m;
        }
        return (sl << 5) + bl;
    }

  private:
    unsigned int length, blocks;
    std::vector<unsigned int> bit, sum;
};
