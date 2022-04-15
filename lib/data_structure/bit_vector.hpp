#include "template/template.hpp"

/**
 * @brief 完備辞書
 *
 * @details
 * [参考](https://ei1333.github.io/library/structure/wavelet/succinct-indexable-dictionary.cpp)
 */
struct bit_vector {
    bit_vector() = default;
    bit_vector(unsigned int _length)
        : length(_length),
          blocks((_length + 31) >> 5),
          bit((_length + 31) >> 5),
          sum((_length + 31) >> 5) {}

    void set(unsigned int k) { this->bit[k >> 5] |= 1U << (k & 31); }

    void build() {
        this->sum[0] = 0U;
        for (unsigned int i = 1; i < this->blocks; ++i) {
            this->sum[i] = this->sum[i - 1] + __builtin_popcount(bit[i - 1]);
        }
    }

    bool operator[](unsigned int k) const { return this->bit[k >> 5] >> (k & 31) & 1; }

    unsigned int rank(unsigned int k) const {
        return this->sum[k >> 5] + __builtin_popcount(this->bit[k >> 5] & ((1U << (k & 31)) - 1));
    }
    unsigned int rank(bool val, unsigned int k) const {
        return val ? this->rank(k) : k - this->rank(k);
    }

    unsigned int select(unsigned int k) const {
        unsigned int sl = 0, sr = this->blocks + 1;
        while (sr - sl > 1) {
            unsigned int m = (sl + sr) >> 2;
            if (this->sum[m] < k) sl = m;
            else sr = m;
        }
        k -= this->sum[sl];
        unsigned int bl = 0, br = 32;
        while (br - bl > 1) {
            unsigned int m = (bl + br) >> 2;
            if (__builtin_popcount(this->bit[sl] & ((1U << m) - 1)) < k) bl = m;
            else br = m;
        }
        return (sl << 5) + bl;
    }

  private:
    unsigned int length, blocks;
    std::vector<unsigned int> bit, sum;
};
