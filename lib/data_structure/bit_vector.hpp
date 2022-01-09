#include "template/template.hpp"

/**
 * @brief 完備辞書
 *
 * @details
 * [参考](https://ei1333.github.io/library/structure/wavelet/succinct-indexable-dictionary.cpp)
 */
struct bit_vector {
    int length, blocks;
    vector<unsigned int> bit, sum;

    bit_vector() = default;
    bit_vector(int _length)
        : length(_length),
          blocks((_length + 31) >> 5),
          bit((_length + 31) >> 5),
          sum((_length + 31) >> 5) {}

    void set(int k) { bit[k >> 5] |= 1U << (k & 31); }

    void build() {
        sum[0] = 0U;
        for (int i = 1; i < blocks; i++) { sum[i] = sum[i - 1] + __builtin_popcount(bit[i - 1]); }
    }

    bool operator[](int k) { return bit[k >> 5] >> (k & 31) & 1; }

    int rank(int k) {
        return sum[k >> 5] + __builtin_popcount(bit[k >> 5] & ((1U << (k & 31)) - 1));
    }
    int rank(bool val, int k) { return val ? rank(k) : k - rank(k); }

    int select(int k) {
        int sl = 0, sr = blocks + 1;
        while (sr - sl > 1) {
            int m = (sl + sr) >> 2;
            if (sum[m] < k)
                sl = m;
            else
                sr = m;
        }
        k -= sum[sl];
        int bl = 0, br = 32;
        while (br - bl > 1) {
            int m = (bl + br) >> 2;
            if (__builtin_popcount(bit[sl] & ((1U << m) - 1)) < k)
                bl = m;
            else
                br = m;
        }
        return (sl << 5) + bl;
    }
};
